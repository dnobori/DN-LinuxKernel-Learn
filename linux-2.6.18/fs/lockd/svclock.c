#include "linux/autoconf.h"
/*
 * linux/fs/lockd/svclock.c
 *
 * Handling of server-side locks, mostly of the blocked variety.
 * This is the ugliest part of lockd because we tread on very thin ice.
 * GRANT and CANCEL calls may get stuck, meet in mid-flight, etc.
 * IMNSHO introducing the grant callback into the NLM protocol was one
 * of the worst ideas Sun ever had. Except maybe for the idea of doing
 * NFS file locking at all.
 *
 * I'm trying hard to avoid race conditions by protecting most accesses
 * to a file's list of blocked locks through a semaphore. The global
 * list of blocked locks is not protected in this fashion however.
 * Therefore, some functions (such as the RPC callback for the async grant
 * call) move blocked locks towards the head of the list *while some other
 * process might be traversing it*. This should not be a problem in
 * practice, because this will only cause functions traversing the list
 * to visit some blocks twice.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/smp_lock.h>
#include <linux/sunrpc/clnt.h>
#include <linux/sunrpc/svc.h>
#include <linux/lockd/nlm.h>
#include <linux/lockd/lockd.h>

#define NLMDBG_FACILITY		NLMDBG_SVCLOCK

#ifdef CONFIG_LOCKD_V4
#define nlm_deadlock	nlm4_deadlock
#else
#define nlm_deadlock	nlm_lck_denied
#endif

static void nlmsvc_release_block(struct nlm_block *block);
static void	nlmsvc_insert_block(struct nlm_block *block, unsigned long);
static int	nlmsvc_remove_block(struct nlm_block *block);

static int nlmsvc_setgrantargs(struct nlm_rqst *call, struct nlm_lock *lock);
static void nlmsvc_freegrantargs(struct nlm_rqst *call);
static const struct rpc_call_ops nlmsvc_grant_ops;

/*
 * The list of blocked locks to retry
 */
static struct nlm_block *	nlm_blocked;

/*
 * Insert a blocked lock into the global list
 */
static void
nlmsvc_insert_block(struct nlm_block *block, unsigned long when)
{
	struct nlm_block **bp, *b;

	dprintk("lockd: nlmsvc_insert_block(%p, %ld)\n", block, when);
	kref_get(&block->b_count);
	if (block->b_queued)
		nlmsvc_remove_block(block);
	bp = &nlm_blocked;
	if (when != NLM_NEVER) {
		if ((when += jiffies) == NLM_NEVER)
			when ++;
		while ((b = *bp) && time_before_eq(b->b_when,when) && b->b_when != NLM_NEVER)
			bp = &b->b_next;
	} else
		while ((b = *bp) != 0)
			bp = &b->b_next;

	block->b_queued = 1;
	block->b_when = when;
	block->b_next = b;
	*bp = block;
}

/*
 * Remove a block from the global list
 */
static int
nlmsvc_remove_block(struct nlm_block *block)
{
	struct nlm_block **bp, *b;

	if (!block->b_queued)
		return 1;
	for (bp = &nlm_blocked; (b = *bp) != 0; bp = &b->b_next) {
		if (b == block) {
			*bp = block->b_next;
			block->b_queued = 0;
			nlmsvc_release_block(block);
			return 1;
		}
	}

	return 0;
}

/*
 * Find a block for a given lock
 */
static struct nlm_block *
nlmsvc_lookup_block(struct nlm_file *file, struct nlm_lock *lock)
{
	struct nlm_block	**head, *block;
	struct file_lock	*fl;

	dprintk("lockd: nlmsvc_lookup_block f=%p pd=%d %Ld-%Ld ty=%d\n",
				file, lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end, lock->fl.fl_type);
	for (head = &nlm_blocked; (block = *head) != 0; head = &block->b_next) {
		fl = &block->b_call->a_args.lock.fl;
		dprintk("lockd: check f=%p pd=%d %Ld-%Ld ty=%d cookie=%s\n",
				block->b_file, fl->fl_pid,
				(long long)fl->fl_start,
				(long long)fl->fl_end, fl->fl_type,
				nlmdbg_cookie2a(&block->b_call->a_args.cookie));
		if (block->b_file == file && nlm_compare_locks(fl, &lock->fl)) {
			kref_get(&block->b_count);
			return block;
		}
	}

	return NULL;
}

static inline int nlm_cookie_match(struct nlm_cookie *a, struct nlm_cookie *b)
{
	if(a->len != b->len)
		return 0;
	if(memcmp(a->data,b->data,a->len))
		return 0;
	return 1;
}

/*
 * Find a block with a given NLM cookie.
 */
static inline struct nlm_block *
nlmsvc_find_block(struct nlm_cookie *cookie,  struct sockaddr_in *sin)
{
	struct nlm_block *block;

	for (block = nlm_blocked; block; block = block->b_next) {
		dprintk("cookie: head of blocked queue %p, block %p\n", 
			nlm_blocked, block);
		if (nlm_cookie_match(&block->b_call->a_args.cookie,cookie)
				&& nlm_cmp_addr(sin, &block->b_host->h_addr))
			break;
	}

	if (block != NULL)
		kref_get(&block->b_count);
	return block;
}

/*
 * Create a block and initialize it.
 *
 * Note: we explicitly set the cookie of the grant reply to that of
 * the blocked lock request. The spec explicitly mentions that the client
 * should _not_ rely on the callback containing the same cookie as the
 * request, but (as I found out later) that's because some implementations
 * do just this. Never mind the standards comittees, they support our
 * logging industries.
 */
static inline struct nlm_block *
nlmsvc_create_block(struct svc_rqst *rqstp, struct nlm_file *file,
				struct nlm_lock *lock, struct nlm_cookie *cookie)
{
	struct nlm_block	*block;
	struct nlm_host		*host;
	struct nlm_rqst		*call = NULL;

	/* Create host handle for callback */
	host = nlmsvc_lookup_host(rqstp);
	if (host == NULL)
		return NULL;

	call = nlm_alloc_call(host);
	if (call == NULL)
		return NULL;

	/* Allocate memory for block, and initialize arguments */
	block = kzalloc(sizeof(*block), GFP_KERNEL);
	if (block == NULL)
		goto failed;
	kref_init(&block->b_count);

	if (!nlmsvc_setgrantargs(call, lock))
		goto failed_free;

	/* Set notifier function for VFS, and init args */
	call->a_args.lock.fl.fl_flags |= FL_SLEEP;
	call->a_args.lock.fl.fl_lmops = &nlmsvc_lock_operations;
	call->a_args.cookie = *cookie;	/* see above */

	dprintk("lockd: created block %p...\n", block);

	/* Create and initialize the block */
	block->b_daemon = rqstp->rq_server;
	block->b_host   = host;
	block->b_file   = file;
	file->f_count++;

	/* Add to file's list of blocks */
	block->b_fnext  = file->f_blocks;
	file->f_blocks  = block;

	/* Set up RPC arguments for callback */
	block->b_call = call;
	call->a_flags   = RPC_TASK_ASYNC;
	call->a_block = block;

	return block;

failed_free:
	kfree(block);
failed:
	nlm_release_call(call);
	return NULL;
}

/*
 * Delete a block. If the lock was cancelled or the grant callback
 * failed, unlock is set to 1.
 * It is the caller's responsibility to check whether the file
 * can be closed hereafter.
 */
static int nlmsvc_unlink_block(struct nlm_block *block)
{
	int status;
	dprintk("lockd: unlinking block %p...\n", block);

	/* Remove block from list */
	status = posix_unblock_lock(block->b_file->f_file, &block->b_call->a_args.lock.fl);
	nlmsvc_remove_block(block);
	return status;
}

static void nlmsvc_free_block(struct kref *kref)
{
	struct nlm_block *block = container_of(kref, struct nlm_block, b_count);
	struct nlm_file		*file = block->b_file;
	struct nlm_block	**bp;

	dprintk("lockd: freeing block %p...\n", block);

	down(&file->f_sema);
	/* Remove block from file's list of blocks */
	for (bp = &file->f_blocks; *bp; bp = &(*bp)->b_fnext) {
		if (*bp == block) {
			*bp = block->b_fnext;
			break;
		}
	}
	up(&file->f_sema);

	nlmsvc_freegrantargs(block->b_call);
	nlm_release_call(block->b_call);
	nlm_release_file(block->b_file);
	kfree(block);
}

static void nlmsvc_release_block(struct nlm_block *block)
{
	if (block != NULL)
		kref_put(&block->b_count, nlmsvc_free_block);
}

static void nlmsvc_act_mark(struct nlm_host *host, struct nlm_file *file)
{
	struct nlm_block *block;

	down(&file->f_sema);
	for (block = file->f_blocks; block != NULL; block = block->b_fnext)
		block->b_host->h_inuse = 1;
	up(&file->f_sema);
}

static void nlmsvc_act_unlock(struct nlm_host *host, struct nlm_file *file)
{
	struct nlm_block *block;

restart:
	down(&file->f_sema);
	for (block = file->f_blocks; block != NULL; block = block->b_fnext) {
		if (host != NULL && host != block->b_host)
			continue;
		if (!block->b_queued)
			continue;
		kref_get(&block->b_count);
		up(&file->f_sema);
		nlmsvc_unlink_block(block);
		nlmsvc_release_block(block);
		goto restart;
	}
	up(&file->f_sema);
}

/*
 * Loop over all blocks and perform the action specified.
 * (NLM_ACT_CHECK handled by nlmsvc_inspect_file).
 */
void
nlmsvc_traverse_blocks(struct nlm_host *host, struct nlm_file *file, int action)
{
	if (action == NLM_ACT_MARK)
		nlmsvc_act_mark(host, file);
	else
		nlmsvc_act_unlock(host, file);
}

/*
 * Initialize arguments for GRANTED call. The nlm_rqst structure
 * has been cleared already.
 */
static int nlmsvc_setgrantargs(struct nlm_rqst *call, struct nlm_lock *lock)
{
	locks_copy_lock(&call->a_args.lock.fl, &lock->fl);
	memcpy(&call->a_args.lock.fh, &lock->fh, sizeof(call->a_args.lock.fh));
	call->a_args.lock.caller = system_utsname.nodename;
	call->a_args.lock.oh.len = lock->oh.len;

	/* set default data area */
	call->a_args.lock.oh.data = call->a_owner;
	call->a_args.lock.svid = lock->fl.fl_pid;

	if (lock->oh.len > NLMCLNT_OHSIZE) {
		void *data = kmalloc(lock->oh.len, GFP_KERNEL);
		if (!data)
			return 0;
		call->a_args.lock.oh.data = (u8 *) data;
	}

	memcpy(call->a_args.lock.oh.data, lock->oh.data, lock->oh.len);
	return 1;
}

static void nlmsvc_freegrantargs(struct nlm_rqst *call)
{
	if (call->a_args.lock.oh.data != call->a_owner)
		kfree(call->a_args.lock.oh.data);
}

/*
 * Attempt to establish a lock, and if it can't be granted, block it
 * if required.
 */
u32
nlmsvc_lock(struct svc_rqst *rqstp, struct nlm_file *file,
			struct nlm_lock *lock, int wait, struct nlm_cookie *cookie)
{
	struct nlm_block	*block, *newblock = NULL;
	int			error;
	u32			ret;

	dprintk("lockd: nlmsvc_lock(%s/%ld, ty=%d, pi=%d, %Ld-%Ld, bl=%d)\n",
				file->f_file->f_dentry->d_inode->i_sb->s_id,
				file->f_file->f_dentry->d_inode->i_ino,
				lock->fl.fl_type, lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end,
				wait);


	lock->fl.fl_flags &= ~FL_SLEEP;
again:
	/* Lock file against concurrent access */
	down(&file->f_sema);
	/* Get existing block (in case client is busy-waiting) */
	block = nlmsvc_lookup_block(file, lock);
	if (block == NULL) {
		if (newblock != NULL)
			lock = &newblock->b_call->a_args.lock;
	} else
		lock = &block->b_call->a_args.lock;

	error = posix_lock_file(file->f_file, &lock->fl);
	lock->fl.fl_flags &= ~FL_SLEEP;

	dprintk("lockd: posix_lock_file returned %d\n", error);

	switch(error) {
		case 0:
			ret = nlm_granted;
			goto out;
		case -EAGAIN:
			break;
		case -EDEADLK:
			ret = nlm_deadlock;
			goto out;
		default:			/* includes ENOLCK */
			ret = nlm_lck_denied_nolocks;
			goto out;
	}

	ret = nlm_lck_denied;
	if (!wait)
		goto out;

	ret = nlm_lck_blocked;
	if (block != NULL)
		goto out;

	/* If we don't have a block, create and initialize it. Then
	 * retry because we may have slept in kmalloc. */
	/* We have to release f_sema as nlmsvc_create_block may try to
	 * to claim it while doing host garbage collection */
	if (newblock == NULL) {
		up(&file->f_sema);
		dprintk("lockd: blocking on this lock (allocating).\n");
		if (!(newblock = nlmsvc_create_block(rqstp, file, lock, cookie)))
			return nlm_lck_denied_nolocks;
		goto again;
	}

	/* Append to list of blocked */
	nlmsvc_insert_block(newblock, NLM_NEVER);
out:
	up(&file->f_sema);
	nlmsvc_release_block(newblock);
	nlmsvc_release_block(block);
	dprintk("lockd: nlmsvc_lock returned %u\n", ret);
	return ret;
}

/*
 * Test for presence of a conflicting lock.
 */
u32
nlmsvc_testlock(struct nlm_file *file, struct nlm_lock *lock,
				       struct nlm_lock *conflock)
{
	dprintk("lockd: nlmsvc_testlock(%s/%ld, ty=%d, %Ld-%Ld)\n",
				file->f_file->f_dentry->d_inode->i_sb->s_id,
				file->f_file->f_dentry->d_inode->i_ino,
				lock->fl.fl_type,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	if (posix_test_lock(file->f_file, &lock->fl, &conflock->fl)) {
		dprintk("lockd: conflicting lock(ty=%d, %Ld-%Ld)\n",
				conflock->fl.fl_type,
				(long long)conflock->fl.fl_start,
				(long long)conflock->fl.fl_end);
		conflock->caller = "somehost";	/* FIXME */
		conflock->oh.len = 0;		/* don't return OH info */
		conflock->svid = conflock->fl.fl_pid;
		return nlm_lck_denied;
	}

	return nlm_granted;
}

/*
 * Remove a lock.
 * This implies a CANCEL call: We send a GRANT_MSG, the client replies
 * with a GRANT_RES call which gets lost, and calls UNLOCK immediately
 * afterwards. In this case the block will still be there, and hence
 * must be removed.
 */
u32
nlmsvc_unlock(struct nlm_file *file, struct nlm_lock *lock)
{
	int	error;

	dprintk("lockd: nlmsvc_unlock(%s/%ld, pi=%d, %Ld-%Ld)\n",
				file->f_file->f_dentry->d_inode->i_sb->s_id,
				file->f_file->f_dentry->d_inode->i_ino,
				lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	/* First, cancel any lock that might be there */
	nlmsvc_cancel_blocked(file, lock);

	lock->fl.fl_type = F_UNLCK;
	error = posix_lock_file(file->f_file, &lock->fl);

	return (error < 0)? nlm_lck_denied_nolocks : nlm_granted;
}

/*
 * Cancel a previously blocked request.
 *
 * A cancel request always overrides any grant that may currently
 * be in progress.
 * The calling procedure must check whether the file can be closed.
 */
u32
nlmsvc_cancel_blocked(struct nlm_file *file, struct nlm_lock *lock)
{
	struct nlm_block	*block;
	int status = 0;

	dprintk("lockd: nlmsvc_cancel(%s/%ld, pi=%d, %Ld-%Ld)\n",
				file->f_file->f_dentry->d_inode->i_sb->s_id,
				file->f_file->f_dentry->d_inode->i_ino,
				lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	down(&file->f_sema);
	block = nlmsvc_lookup_block(file, lock);
	up(&file->f_sema);
	if (block != NULL) {
		status = nlmsvc_unlink_block(block);
		nlmsvc_release_block(block);
	}
	return status ? nlm_lck_denied : nlm_granted;
}

/*
 * Unblock a blocked lock request. This is a callback invoked from the
 * VFS layer when a lock on which we blocked is removed.
 *
 * This function doesn't grant the blocked lock instantly, but rather moves
 * the block to the head of nlm_blocked where it can be picked up by lockd.
 */
static void
nlmsvc_notify_blocked(struct file_lock *fl)
{
	struct nlm_block	**bp, *block;

	dprintk("lockd: VFS unblock notification for block %p\n", fl);
	for (bp = &nlm_blocked; (block = *bp) != 0; bp = &block->b_next) {
		if (nlm_compare_locks(&block->b_call->a_args.lock.fl, fl)) {
			nlmsvc_insert_block(block, 0);
			svc_wake_up(block->b_daemon);
			return;
		}
	}

	printk(KERN_WARNING "lockd: notification for unknown block!\n");
}

static int nlmsvc_same_owner(struct file_lock *fl1, struct file_lock *fl2)
{
	return fl1->fl_owner == fl2->fl_owner && fl1->fl_pid == fl2->fl_pid;
}

struct lock_manager_operations nlmsvc_lock_operations = {
	.fl_compare_owner = nlmsvc_same_owner,
	.fl_notify = nlmsvc_notify_blocked,
};

/*
 * Try to claim a lock that was previously blocked.
 *
 * Note that we use both the RPC_GRANTED_MSG call _and_ an async
 * RPC thread when notifying the client. This seems like overkill...
 * Here's why:
 *  -	we don't want to use a synchronous RPC thread, otherwise
 *	we might find ourselves hanging on a dead portmapper.
 *  -	Some lockd implementations (e.g. HP) don't react to
 *	RPC_GRANTED calls; they seem to insist on RPC_GRANTED_MSG calls.
 */
static void
nlmsvc_grant_blocked(struct nlm_block *block)
{
	struct nlm_file		*file = block->b_file;
	struct nlm_lock		*lock = &block->b_call->a_args.lock;
	int			error;

	dprintk("lockd: grant blocked lock %p\n", block);

	/* Unlink block request from list */
	nlmsvc_unlink_block(block);

	/* If b_granted is true this means we've been here before.
	 * Just retry the grant callback, possibly refreshing the RPC
	 * binding */
	if (block->b_granted) {
		nlm_rebind_host(block->b_host);
		goto callback;
	}

	/* Try the lock operation again */
	lock->fl.fl_flags |= FL_SLEEP;
	error = posix_lock_file(file->f_file, &lock->fl);
	lock->fl.fl_flags &= ~FL_SLEEP;

	switch (error) {
	case 0:
		break;
	case -EAGAIN:
		dprintk("lockd: lock still blocked\n");
		nlmsvc_insert_block(block, NLM_NEVER);
		return;
	default:
		printk(KERN_WARNING "lockd: unexpected error %d in %s!\n",
				-error, __FUNCTION__);
		nlmsvc_insert_block(block, 10 * HZ);
		return;
	}

callback:
	/* Lock was granted by VFS. */
	dprintk("lockd: GRANTing blocked lock.\n");
	block->b_granted = 1;

	/* Schedule next grant callback in 30 seconds */
	nlmsvc_insert_block(block, 30 * HZ);

	/* Call the client */
	kref_get(&block->b_count);
	if (nlm_async_call(block->b_call, NLMPROC_GRANTED_MSG,
						&nlmsvc_grant_ops) < 0)
		nlmsvc_release_block(block);
}

/*
 * This is the callback from the RPC layer when the NLM_GRANTED_MSG
 * RPC call has succeeded or timed out.
 * Like all RPC callbacks, it is invoked by the rpciod process, so it
 * better not sleep. Therefore, we put the blocked lock on the nlm_blocked
 * chain once more in order to have it removed by lockd itself (which can
 * then sleep on the file semaphore without disrupting e.g. the nfs client).
 */
static void nlmsvc_grant_callback(struct rpc_task *task, void *data)
{
	struct nlm_rqst		*call = data;
	struct nlm_block	*block = call->a_block;
	unsigned long		timeout;

	dprintk("lockd: GRANT_MSG RPC callback\n");

	/* Technically, we should down the file semaphore here. Since we
	 * move the block towards the head of the queue only, no harm
	 * can be done, though. */
	if (task->tk_status < 0) {
		/* RPC error: Re-insert for retransmission */
		timeout = 10 * HZ;
	} else {
		/* Call was successful, now wait for client callback */
		timeout = 60 * HZ;
	}
	nlmsvc_insert_block(block, timeout);
	svc_wake_up(block->b_daemon);
}

static void nlmsvc_grant_release(void *data)
{
	struct nlm_rqst		*call = data;

	nlmsvc_release_block(call->a_block);
}

static const struct rpc_call_ops nlmsvc_grant_ops = {
	.rpc_call_done = nlmsvc_grant_callback,
	.rpc_release = nlmsvc_grant_release,
};

/*
 * We received a GRANT_RES callback. Try to find the corresponding
 * block.
 */
void
nlmsvc_grant_reply(struct svc_rqst *rqstp, struct nlm_cookie *cookie, u32 status)
{
	struct nlm_block	*block;
	struct nlm_file		*file;

	dprintk("grant_reply: looking for cookie %x, host (%08x), s=%d \n", 
		*(unsigned int *)(cookie->data), 
		ntohl(rqstp->rq_addr.sin_addr.s_addr), status);
	if (!(block = nlmsvc_find_block(cookie, &rqstp->rq_addr)))
		return;
	file = block->b_file;

	if (block) {
		if (status == NLM_LCK_DENIED_GRACE_PERIOD) {
			/* Try again in a couple of seconds */
			nlmsvc_insert_block(block, 10 * HZ);
		} else {
			/* Lock is now held by client, or has been rejected.
			 * In both cases, the block should be removed. */
			nlmsvc_unlink_block(block);
		}
	}
	nlmsvc_release_block(block);
}

/*
 * Retry all blocked locks that have been notified. This is where lockd
 * picks up locks that can be granted, or grant notifications that must
 * be retransmitted.
 */
unsigned long
nlmsvc_retry_blocked(void)
{
	struct nlm_block	*block;

	dprintk("nlmsvc_retry_blocked(%p, when=%ld)\n",
			nlm_blocked,
			nlm_blocked? nlm_blocked->b_when : 0);
	while ((block = nlm_blocked) != 0) {
		if (block->b_when == NLM_NEVER)
			break;
	        if (time_after(block->b_when,jiffies))
			break;
		dprintk("nlmsvc_retry_blocked(%p, when=%ld)\n",
			block, block->b_when);
		kref_get(&block->b_count);
		nlmsvc_grant_blocked(block);
		nlmsvc_release_block(block);
	}

	if ((block = nlm_blocked) && block->b_when != NLM_NEVER)
		return (block->b_when - jiffies);

	return MAX_SCHEDULE_TIMEOUT;
}
