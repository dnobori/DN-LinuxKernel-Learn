#include "linux/generated/autoconf.h"
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef __XFS_BUF_H__
#define __XFS_BUF_H__

#include <linux/list.h>
#include <linux/types.h>
#include <linux/spinlock.h>
#include <asm/system.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/buffer_head.h>
#include <linux/uio.h>

/*
 *	Base types
 */

#define XFS_BUF_DADDR_NULL	((xfs_daddr_t) (-1LL))

#define xfs_buf_ctob(pp)	((pp) * PAGE_CACHE_SIZE)
#define xfs_buf_btoc(dd)	(((dd) + PAGE_CACHE_SIZE-1) >> PAGE_CACHE_SHIFT)
#define xfs_buf_btoct(dd)	((dd) >> PAGE_CACHE_SHIFT)
#define xfs_buf_poff(aa)	((aa) & ~PAGE_CACHE_MASK)

typedef enum {
	XBRW_READ = 1,			/* transfer into target memory */
	XBRW_WRITE = 2,			/* transfer from target memory */
	XBRW_ZERO = 3,			/* Zero target memory */
} xfs_buf_rw_t;

#define XBF_READ	(1 << 0) /* buffer intended for reading from device */
#define XBF_WRITE	(1 << 1) /* buffer intended for writing to device */
#define XBF_MAPPED	(1 << 2) /* buffer mapped (b_addr valid) */
#define XBF_ASYNC	(1 << 4) /* initiator will not wait for completion */
#define XBF_DONE	(1 << 5) /* all pages in the buffer uptodate */
#define XBF_DELWRI	(1 << 6) /* buffer has dirty pages */
#define XBF_STALE	(1 << 7) /* buffer has been staled, do not find it */
#define XBF_ORDERED	(1 << 11)/* use ordered writes */
#define XBF_READ_AHEAD	(1 << 12)/* asynchronous read-ahead */
#define XBF_LOG_BUFFER	(1 << 13)/* this is a buffer used for the log */

/* flags used only as arguments to access routines */
#define XBF_LOCK	(1 << 14)/* lock requested */
#define XBF_TRYLOCK	(1 << 15)/* lock requested, but do not wait */
#define XBF_DONT_BLOCK	(1 << 16)/* do not block in current thread */

/* flags used only internally */
#define _XBF_PAGES	(1 << 18)/* backed by refcounted pages */
#define	_XBF_RUN_QUEUES	(1 << 19)/* run block device task queue	*/
#define	_XBF_KMEM	(1 << 20)/* backed by heap memory */
#define _XBF_DELWRI_Q	(1 << 21)/* buffer on delwri queue */

typedef unsigned int xfs_buf_flags_t;

#define XFS_BUF_FLAGS \
	{ XBF_READ,		"READ" }, \
	{ XBF_WRITE,		"WRITE" }, \
	{ XBF_MAPPED,		"MAPPED" }, \
	{ XBF_ASYNC,		"ASYNC" }, \
	{ XBF_DONE,		"DONE" }, \
	{ XBF_DELWRI,		"DELWRI" }, \
	{ XBF_STALE,		"STALE" }, \
	{ XBF_ORDERED,		"ORDERED" }, \
	{ XBF_READ_AHEAD,	"READ_AHEAD" }, \
	{ XBF_LOCK,		"LOCK" },  	/* should never be set */\
	{ XBF_TRYLOCK,		"TRYLOCK" }, 	/* ditto */\
	{ XBF_DONT_BLOCK,	"DONT_BLOCK" },	/* ditto */\
	{ _XBF_PAGES,		"PAGES" }, \
	{ _XBF_RUN_QUEUES,	"RUN_QUEUES" }, \
	{ _XBF_KMEM,		"KMEM" }, \
	{ _XBF_DELWRI_Q,	"DELWRI_Q" }

typedef enum {
	XBT_FORCE_SLEEP = 0,
	XBT_FORCE_FLUSH = 1,
} xfs_buftarg_flags_t;

typedef struct xfs_bufhash {
	struct list_head	bh_list;
	spinlock_t		bh_lock;
} xfs_bufhash_t;

typedef struct xfs_buftarg {
	dev_t			bt_dev;
	struct block_device	*bt_bdev;
	struct backing_dev_info	*bt_bdi;
	struct xfs_mount	*bt_mount;
	unsigned int		bt_bsize;
	unsigned int		bt_sshift;
	size_t			bt_smask;

	/* per device delwri queue */
	struct task_struct	*bt_task;
	struct list_head	bt_delwrite_queue;
	spinlock_t		bt_delwrite_lock;
	unsigned long		bt_flags;

	/* LRU control structures */
	struct shrinker		bt_shrinker;
	struct list_head	bt_lru;
	spinlock_t		bt_lru_lock;
	unsigned int		bt_lru_nr;
} xfs_buftarg_t;

struct xfs_buf;
typedef void (*xfs_buf_iodone_t)(struct xfs_buf *);

#define XB_PAGES	2

typedef struct xfs_buf {
	/*
	 * first cacheline holds all the fields needed for an uncontended cache
	 * hit to be fully processed. The semaphore straddles the cacheline
	 * boundary, but the counter and lock sits on the first cacheline,
	 * which is the only bit that is touched if we hit the semaphore
	 * fast-path on locking.
	 */
	struct rb_node		b_rbnode;	/* rbtree node */
	xfs_off_t		b_file_offset;	/* offset in file */
	size_t			b_buffer_length;/* size of buffer in bytes */
	atomic_t		b_hold;		/* reference count */
	atomic_t		b_lru_ref;	/* lru reclaim ref count */
	xfs_buf_flags_t		b_flags;	/* status flags */
	struct semaphore	b_sema;		/* semaphore for lockables */

	struct list_head	b_lru;		/* lru list */
	wait_queue_head_t	b_waiters;	/* unpin waiters */
	struct list_head	b_list;
	struct xfs_perag	*b_pag;		/* contains rbtree root */
	xfs_buftarg_t		*b_target;	/* buffer target (device) */
	xfs_daddr_t		b_bn;		/* block number for I/O */
	size_t			b_count_desired;/* desired transfer size */
	void			*b_addr;	/* virtual address of buffer */
	struct work_struct	b_iodone_work;
	xfs_buf_iodone_t	b_iodone;	/* I/O completion function */
	struct completion	b_iowait;	/* queue for I/O waiters */
	void			*b_fspriv;
	void			*b_fspriv2;
	struct page		**b_pages;	/* array of page pointers */
	struct page		*b_page_array[XB_PAGES]; /* inline pages */
	unsigned long		b_queuetime;	/* time buffer was queued */
	atomic_t		b_pin_count;	/* pin count */
	atomic_t		b_io_remaining;	/* #outstanding I/O requests */
	unsigned int		b_page_count;	/* size of page array */
	unsigned int		b_offset;	/* page offset in first page */
	unsigned short		b_error;	/* error code on I/O */
#ifdef XFS_BUF_LOCK_TRACKING
	int			b_last_holder;
#endif
} xfs_buf_t;


/* Finding and Reading Buffers */
extern xfs_buf_t *_xfs_buf_find(xfs_buftarg_t *, xfs_off_t, size_t,
				xfs_buf_flags_t, xfs_buf_t *);
#define xfs_incore(buftarg,blkno,len,lockit) \
	_xfs_buf_find(buftarg, blkno ,len, lockit, NULL)

extern xfs_buf_t *xfs_buf_get(xfs_buftarg_t *, xfs_off_t, size_t,
				xfs_buf_flags_t);
extern xfs_buf_t *xfs_buf_read(xfs_buftarg_t *, xfs_off_t, size_t,
				xfs_buf_flags_t);

extern xfs_buf_t *xfs_buf_get_empty(size_t, xfs_buftarg_t *);
extern xfs_buf_t *xfs_buf_get_uncached(struct xfs_buftarg *, size_t, int);
extern int xfs_buf_associate_memory(xfs_buf_t *, void *, size_t);
extern void xfs_buf_hold(xfs_buf_t *);
extern void xfs_buf_readahead(xfs_buftarg_t *, xfs_off_t, size_t);
struct xfs_buf *xfs_buf_read_uncached(struct xfs_mount *mp,
				struct xfs_buftarg *target,
				xfs_daddr_t daddr, size_t length, int flags);

/* Releasing Buffers */
extern void xfs_buf_free(xfs_buf_t *);
extern void xfs_buf_rele(xfs_buf_t *);

/* Locking and Unlocking Buffers */
extern int xfs_buf_cond_lock(xfs_buf_t *);
extern int xfs_buf_lock_value(xfs_buf_t *);
extern void xfs_buf_lock(xfs_buf_t *);
extern void xfs_buf_unlock(xfs_buf_t *);

/* Buffer Read and Write Routines */
extern int xfs_bwrite(struct xfs_mount *mp, struct xfs_buf *bp);
extern void xfs_bdwrite(void *mp, xfs_buf_t *bp);

extern void xfsbdstrat(struct xfs_mount *, struct xfs_buf *);
extern int xfs_bdstrat_cb(struct xfs_buf *);

extern void xfs_buf_ioend(xfs_buf_t *,	int);
extern void xfs_buf_ioerror(xfs_buf_t *, int);
extern int xfs_buf_iorequest(xfs_buf_t *);
extern int xfs_buf_iowait(xfs_buf_t *);
extern void xfs_buf_iomove(xfs_buf_t *, size_t, size_t, void *,
				xfs_buf_rw_t);
#define xfs_buf_zero(bp, off, len) \
	    xfs_buf_iomove((bp), (off), (len), NULL, XBRW_ZERO)

static inline int xfs_buf_geterror(xfs_buf_t *bp)
{
	return bp ? bp->b_error : ENOMEM;
}

/* Buffer Utility Routines */
extern xfs_caddr_t xfs_buf_offset(xfs_buf_t *, size_t);

/* Delayed Write Buffer Routines */
extern void xfs_buf_delwri_dequeue(xfs_buf_t *);
extern void xfs_buf_delwri_promote(xfs_buf_t *);

/* Buffer Daemon Setup Routines */
extern int xfs_buf_init(void);
extern void xfs_buf_terminate(void);

#define xfs_buf_target_name(target)	\
	({ char __b[BDEVNAME_SIZE]; bdevname((target)->bt_bdev, __b); __b; })


#define XFS_BUF_BFLAGS(bp)	((bp)->b_flags)
#define XFS_BUF_ZEROFLAGS(bp)	((bp)->b_flags &= \
		~(XBF_READ|XBF_WRITE|XBF_ASYNC|XBF_DELWRI|XBF_ORDERED))

void xfs_buf_stale(struct xfs_buf *bp);
#define XFS_BUF_STALE(bp)	xfs_buf_stale(bp);
#define XFS_BUF_UNSTALE(bp)	((bp)->b_flags &= ~XBF_STALE)
#define XFS_BUF_ISSTALE(bp)	((bp)->b_flags & XBF_STALE)
#define XFS_BUF_SUPER_STALE(bp)	do {				\
					XFS_BUF_STALE(bp);	\
					xfs_buf_delwri_dequeue(bp);	\
					XFS_BUF_DONE(bp);	\
				} while (0)

#define XFS_BUF_DELAYWRITE(bp)		((bp)->b_flags |= XBF_DELWRI)
#define XFS_BUF_UNDELAYWRITE(bp)	xfs_buf_delwri_dequeue(bp)
#define XFS_BUF_ISDELAYWRITE(bp)	((bp)->b_flags & XBF_DELWRI)

#define XFS_BUF_ERROR(bp,no)	xfs_buf_ioerror(bp,no)
#define XFS_BUF_GETERROR(bp)	xfs_buf_geterror(bp)
#define XFS_BUF_ISERROR(bp)	(xfs_buf_geterror(bp) ? 1 : 0)

#define XFS_BUF_DONE(bp)	((bp)->b_flags |= XBF_DONE)
#define XFS_BUF_UNDONE(bp)	((bp)->b_flags &= ~XBF_DONE)
#define XFS_BUF_ISDONE(bp)	((bp)->b_flags & XBF_DONE)

#define XFS_BUF_BUSY(bp)	do { } while (0)
#define XFS_BUF_UNBUSY(bp)	do { } while (0)
#define XFS_BUF_ISBUSY(bp)	(1)

#define XFS_BUF_ASYNC(bp)	((bp)->b_flags |= XBF_ASYNC)
#define XFS_BUF_UNASYNC(bp)	((bp)->b_flags &= ~XBF_ASYNC)
#define XFS_BUF_ISASYNC(bp)	((bp)->b_flags & XBF_ASYNC)

#define XFS_BUF_ORDERED(bp)	((bp)->b_flags |= XBF_ORDERED)
#define XFS_BUF_UNORDERED(bp)	((bp)->b_flags &= ~XBF_ORDERED)
#define XFS_BUF_ISORDERED(bp)	((bp)->b_flags & XBF_ORDERED)

#define XFS_BUF_HOLD(bp)	xfs_buf_hold(bp)
#define XFS_BUF_READ(bp)	((bp)->b_flags |= XBF_READ)
#define XFS_BUF_UNREAD(bp)	((bp)->b_flags &= ~XBF_READ)
#define XFS_BUF_ISREAD(bp)	((bp)->b_flags & XBF_READ)

#define XFS_BUF_WRITE(bp)	((bp)->b_flags |= XBF_WRITE)
#define XFS_BUF_UNWRITE(bp)	((bp)->b_flags &= ~XBF_WRITE)
#define XFS_BUF_ISWRITE(bp)	((bp)->b_flags & XBF_WRITE)

#define XFS_BUF_IODONE_FUNC(bp)			((bp)->b_iodone)
#define XFS_BUF_SET_IODONE_FUNC(bp, func)	((bp)->b_iodone = (func))
#define XFS_BUF_CLR_IODONE_FUNC(bp)		((bp)->b_iodone = NULL)

#define XFS_BUF_FSPRIVATE(bp, type)		((type)(bp)->b_fspriv)
#define XFS_BUF_SET_FSPRIVATE(bp, val)		((bp)->b_fspriv = (void*)(val))
#define XFS_BUF_FSPRIVATE2(bp, type)		((type)(bp)->b_fspriv2)
#define XFS_BUF_SET_FSPRIVATE2(bp, val)		((bp)->b_fspriv2 = (void*)(val))
#define XFS_BUF_SET_START(bp)			do { } while (0)

#define XFS_BUF_PTR(bp)			(xfs_caddr_t)((bp)->b_addr)
#define XFS_BUF_SET_PTR(bp, val, cnt)	xfs_buf_associate_memory(bp, val, cnt)
#define XFS_BUF_ADDR(bp)		((bp)->b_bn)
#define XFS_BUF_SET_ADDR(bp, bno)	((bp)->b_bn = (xfs_daddr_t)(bno))
#define XFS_BUF_OFFSET(bp)		((bp)->b_file_offset)
#define XFS_BUF_SET_OFFSET(bp, off)	((bp)->b_file_offset = (off))
#define XFS_BUF_COUNT(bp)		((bp)->b_count_desired)
#define XFS_BUF_SET_COUNT(bp, cnt)	((bp)->b_count_desired = (cnt))
#define XFS_BUF_SIZE(bp)		((bp)->b_buffer_length)
#define XFS_BUF_SET_SIZE(bp, cnt)	((bp)->b_buffer_length = (cnt))

static inline void
xfs_buf_set_ref(
	struct xfs_buf	*bp,
	int		lru_ref)
{
	atomic_set(&bp->b_lru_ref, lru_ref);
}
#define XFS_BUF_SET_VTYPE_REF(bp, type, ref)	xfs_buf_set_ref(bp, ref)
#define XFS_BUF_SET_VTYPE(bp, type)		do { } while (0)

#define XFS_BUF_ISPINNED(bp)	atomic_read(&((bp)->b_pin_count))

#define XFS_BUF_VALUSEMA(bp)	xfs_buf_lock_value(bp)
#define XFS_BUF_CPSEMA(bp)	(xfs_buf_cond_lock(bp) == 0)
#define XFS_BUF_VSEMA(bp)	xfs_buf_unlock(bp)
#define XFS_BUF_PSEMA(bp,x)	xfs_buf_lock(bp)
#define XFS_BUF_FINISH_IOWAIT(bp)	complete(&bp->b_iowait);

#define XFS_BUF_SET_TARGET(bp, target)	((bp)->b_target = (target))
#define XFS_BUF_TARGET(bp)		((bp)->b_target)
#define XFS_BUFTARG_NAME(target)	xfs_buf_target_name(target)

static inline void xfs_buf_relse(xfs_buf_t *bp)
{
	xfs_buf_unlock(bp);
	xfs_buf_rele(bp);
}

/*
 *	Handling of buftargs.
 */
extern xfs_buftarg_t *xfs_alloc_buftarg(struct xfs_mount *,
			struct block_device *, int, const char *);
extern void xfs_free_buftarg(struct xfs_mount *, struct xfs_buftarg *);
extern void xfs_wait_buftarg(xfs_buftarg_t *);
extern int xfs_setsize_buftarg(xfs_buftarg_t *, unsigned int, unsigned int);
extern int xfs_flush_buftarg(xfs_buftarg_t *, int);

#ifdef CONFIG_KDB_MODULES
extern struct list_head *xfs_get_buftarg_list(void);
#endif

#define xfs_getsize_buftarg(buftarg)	block_size((buftarg)->bt_bdev)
#define xfs_readonly_buftarg(buftarg)	bdev_read_only((buftarg)->bt_bdev)

#define xfs_binval(buftarg)		xfs_flush_buftarg(buftarg, 1)
#define XFS_bflush(buftarg)		xfs_flush_buftarg(buftarg, 1)

#endif	/* __XFS_BUF_H__ */
