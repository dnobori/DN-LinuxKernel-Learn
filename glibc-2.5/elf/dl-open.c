/* Load a shared object at runtime, relocate it, and run its initializer.
   Copyright (C) 1996-2004, 2005, 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <assert.h>
#include <dlfcn.h>
#include <errno.h>
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>		/* Check whether MAP_COPY is defined.  */
#include <sys/param.h>
#include <bits/libc-lock.h>
#include <ldsodefs.h>
#include <bp-sym.h>
#include <caller.h>

#include <dl-dst.h>


extern ElfW(Addr) _dl_sysdep_start (void **start_argptr,
				    void (*dl_main) (const ElfW(Phdr) *phdr,
						     ElfW(Word) phnum,
						     ElfW(Addr) *user_entry));
weak_extern (BP_SYM (_dl_sysdep_start))

extern int __libc_multiple_libcs;	/* Defined in init-first.c.  */

/* Undefine the following for debugging.  */
/* #define SCOPE_DEBUG 1 */
#ifdef SCOPE_DEBUG
static void show_scope (struct link_map *new);
#endif

/* We must be carefull not to leave us in an inconsistent state.  Thus we
   catch any error and re-raise it after cleaning up.  */

struct dl_open_args
{
  const char *file;
  int mode;
  /* This is the caller of the dlopen() function.  */
  const void *caller_dlopen;
  /* This is the caller if _dl_open().  */
  const void *caller_dl_open;
  struct link_map *map;
  /* Namespace ID.  */
  Lmid_t nsid;
  /* Original parameters to the program and the current environment.  */
  int argc;
  char **argv;
  char **env;
};


static int
add_to_global (struct link_map *new)
{
  struct link_map **new_global;
  unsigned int to_add = 0;
  unsigned int cnt;

  /* Count the objects we have to put in the global scope.  */
  for (cnt = 0; cnt < new->l_searchlist.r_nlist; ++cnt)
    if (new->l_searchlist.r_list[cnt]->l_global == 0)
      ++to_add;

  /* The symbols of the new objects and its dependencies are to be
     introduced into the global scope that will be used to resolve
     references from other dynamically-loaded objects.

     The global scope is the searchlist in the main link map.  We
     extend this list if necessary.  There is one problem though:
     since this structure was allocated very early (before the libc
     is loaded) the memory it uses is allocated by the malloc()-stub
     in the ld.so.  When we come here these functions are not used
     anymore.  Instead the malloc() implementation of the libc is
     used.  But this means the block from the main map cannot be used
     in an realloc() call.  Therefore we allocate a completely new
     array the first time we have to add something to the locale scope.  */

  if (GL(dl_ns)[new->l_ns]._ns_global_scope_alloc == 0)
    {
      /* This is the first dynamic object given global scope.  */
      GL(dl_ns)[new->l_ns]._ns_global_scope_alloc
	= GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_nlist + to_add + 8;
      new_global = (struct link_map **)
	malloc (GL(dl_ns)[new->l_ns]._ns_global_scope_alloc
		* sizeof (struct link_map *));
      if (new_global == NULL)
	{
	  GL(dl_ns)[new->l_ns]._ns_global_scope_alloc = 0;
	nomem:
	  _dl_signal_error (ENOMEM, new->l_libname->name, NULL,
			    N_("cannot extend global scope"));
	  return 1;
	}

      /* Copy over the old entries.  */
      GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_list
	= memcpy (new_global,
		  GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_list,
		  (GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_nlist
		   * sizeof (struct link_map *)));
    }
  else if (GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_nlist + to_add
	   > GL(dl_ns)[new->l_ns]._ns_global_scope_alloc)
    {
      /* We have to extend the existing array of link maps in the
	 main map.  */
      new_global = (struct link_map **)
	realloc (GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_list,
		 ((GL(dl_ns)[new->l_ns]._ns_global_scope_alloc + to_add + 8)
		  * sizeof (struct link_map *)));
      if (new_global == NULL)
	goto nomem;

      GL(dl_ns)[new->l_ns]._ns_global_scope_alloc += to_add + 8;
      GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_list = new_global;
    }

  /* Now add the new entries.  */
  for (cnt = 0; cnt < new->l_searchlist.r_nlist; ++cnt)
    {
      struct link_map *map = new->l_searchlist.r_list[cnt];

      if (map->l_global == 0)
	{
	  map->l_global = 1;
	  GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_list[GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_nlist]
	    = map;
	  ++GL(dl_ns)[new->l_ns]._ns_main_searchlist->r_nlist;
	}
    }

  return 0;
}


static void
dl_open_worker (void *a)
{
  struct dl_open_args *args = a;
  const char *file = args->file;
  int mode = args->mode;
  struct link_map *new, *l;
  int lazy;
  unsigned int i;
#ifdef USE_TLS
  bool any_tls = false;
#endif
  struct link_map *call_map = NULL;

  /* Check whether _dl_open() has been called from a valid DSO.  */
  if (__check_caller (args->caller_dl_open,
		      allow_libc|allow_libdl|allow_ldso) != 0)
    _dl_signal_error (0, "dlopen", NULL, N_("invalid caller"));

  /* Determine the caller's map if necessary.  This is needed in case
     we have a DST, when we don't know the namespace ID we have to put
     the new object in, or when the file name has no path in which
     case we need to look along the RUNPATH/RPATH of the caller.  */
  const char *dst = strchr (file, '$');
  if (dst != NULL || args->nsid == __LM_ID_CALLER
      || strchr (file, '/') == NULL)
    {
      const void *caller_dlopen = args->caller_dlopen;

      /* We have to find out from which object the caller is calling.
	 By default we assume this is the main application.  */
      call_map = GL(dl_ns)[LM_ID_BASE]._ns_loaded;

      for (Lmid_t ns = 0; ns < DL_NNS; ++ns)
	for (l = GL(dl_ns)[ns]._ns_loaded; l != NULL; l = l->l_next)
	  if (caller_dlopen >= (const void *) l->l_map_start
	      && caller_dlopen < (const void *) l->l_map_end)
	    {
	      /* There must be exactly one DSO for the range of the virtual
		 memory.  Otherwise something is really broken.  */
	      assert (ns == l->l_ns);
	      call_map = l;
	      goto found_caller;
	    }

    found_caller:
      if (args->nsid == __LM_ID_CALLER)
	{
#ifndef SHARED
	  /* In statically linked apps there might be no loaded object.  */
	  if (call_map == NULL)
	    args->nsid = LM_ID_BASE;
	  else
#endif
	    args->nsid = call_map->l_ns;
	}
    }

  assert (_dl_debug_initialize (0, args->nsid)->r_state == RT_CONSISTENT);

  /* Maybe we have to expand a DST.  */
  if (__builtin_expect (dst != NULL, 0))
    {
      size_t len = strlen (file);
      size_t required;
      char *new_file;

      /* Determine how much space we need.  We have to allocate the
	 memory locally.  */
      required = DL_DST_REQUIRED (call_map, file, len, _dl_dst_count (dst, 0));

      /* Get space for the new file name.  */
      new_file = (char *) alloca (required + 1);

      /* Generate the new file name.  */
      _dl_dst_substitute (call_map, file, new_file, 0);

      /* If the substitution failed don't try to load.  */
      if (*new_file == '\0')
	_dl_signal_error (0, "dlopen", NULL,
			  N_("empty dynamic string token substitution"));

      /* Now we have a new file name.  */
      file = new_file;

      /* It does not matter whether call_map is set even if we
	 computed it only because of the DST.  Since the path contains
	 a slash the value is not used.  See dl-load.c.  */
    }

  /* Load the named object.  */
  args->map = new = _dl_map_object (call_map, file, 0, lt_loaded, 0,
				    mode | __RTLD_CALLMAP, args->nsid);

  /* If the pointer returned is NULL this means the RTLD_NOLOAD flag is
     set and the object is not already loaded.  */
  if (new == NULL)
    {
      assert (mode & RTLD_NOLOAD);
      return;
    }

  if (__builtin_expect (mode & __RTLD_SPROF, 0))
    /* This happens only if we load a DSO for 'sprof'.  */
    return;

  /* This object is directly loaded.  */
  ++new->l_direct_opencount;

  /* It was already open.  */
  if (__builtin_expect (new->l_searchlist.r_list != NULL, 0))
    {
      /* Let the user know about the opencount.  */
      if (__builtin_expect (GLRO(dl_debug_mask) & DL_DEBUG_FILES, 0))
	_dl_debug_printf ("opening file=%s [%lu]; direct_opencount=%u\n\n",
			  new->l_name, new->l_ns, new->l_direct_opencount);

      /* If the user requested the object to be in the global namespace
	 but it is not so far, add it now.  */
      if ((mode & RTLD_GLOBAL) && new->l_global == 0)
	(void) add_to_global (new);

      assert (_dl_debug_initialize (0, args->nsid)->r_state == RT_CONSISTENT);

      return;
    }

  /* Load that object's dependencies.  */
  _dl_map_object_deps (new, NULL, 0, 0,
		       mode & (__RTLD_DLOPEN | RTLD_DEEPBIND | __RTLD_AUDIT));

  /* So far, so good.  Now check the versions.  */
  for (i = 0; i < new->l_searchlist.r_nlist; ++i)
    if (new->l_searchlist.r_list[i]->l_real->l_versions == NULL)
      (void) _dl_check_map_versions (new->l_searchlist.r_list[i]->l_real,
				     0, 0);

#ifdef SCOPE_DEBUG
  show_scope (new);
#endif

#ifdef SHARED
  /* Auditing checkpoint: we have added all objects.  */
  if (__builtin_expect (GLRO(dl_naudit) > 0, 0))
    {
      struct link_map *head = GL(dl_ns)[new->l_ns]._ns_loaded;
      /* Do not call the functions for any auditing object.  */
      if (head->l_auditing == 0)
	{
	  struct audit_ifaces *afct = GLRO(dl_audit);
	  for (unsigned int cnt = 0; cnt < GLRO(dl_naudit); ++cnt)
	    {
	      if (afct->activity != NULL)
		afct->activity (&head->l_audit[cnt].cookie, LA_ACT_CONSISTENT);

	      afct = afct->next;
	    }
	}
    }
#endif

  /* Notify the debugger all new objects are now ready to go.  */
  struct r_debug *r = _dl_debug_initialize (0, args->nsid);
  r->r_state = RT_CONSISTENT;
  _dl_debug_state ();

  /* Only do lazy relocation if `LD_BIND_NOW' is not set.  */
  lazy = (mode & RTLD_BINDING_MASK) == RTLD_LAZY && GLRO(dl_lazy);

  /* Relocate the objects loaded.  We do this in reverse order so that copy
     relocs of earlier objects overwrite the data written by later objects.  */

  l = new;
  while (l->l_next)
    l = l->l_next;
  while (1)
    {
      if (! l->l_real->l_relocated)
	{
#ifdef SHARED
	  if (__builtin_expect (GLRO(dl_profile) != NULL, 0))
	    {
	      /* If this here is the shared object which we want to profile
		 make sure the profile is started.  We can find out whether
	         this is necessary or not by observing the `_dl_profile_map'
	         variable.  If was NULL but is not NULL afterwars we must
		 start the profiling.  */
	      struct link_map *old_profile_map = GL(dl_profile_map);

	      _dl_relocate_object (l, l->l_scope, 1, 1);

	      if (old_profile_map == NULL && GL(dl_profile_map) != NULL)
		{
		  /* We must prepare the profiling.  */
		  _dl_start_profile ();

		  /* Prevent unloading the object.  */
		  GL(dl_profile_map)->l_flags_1 |= DF_1_NODELETE;
		}
	    }
	  else
#endif
	    _dl_relocate_object (l, l->l_scope, lazy, 0);
	}

      if (l == new)
	break;
      l = l->l_prev;
    }

  /* If the file is not loaded now as a dependency, add the search
     list of the newly loaded object to the scope.  */
  for (i = 0; i < new->l_searchlist.r_nlist; ++i)
    {
      struct link_map *imap = new->l_searchlist.r_list[i];

      /* If the initializer has been called already, the object has
	 not been loaded here and now.  */
      if (imap->l_init_called && imap->l_type == lt_loaded)
	{
	  struct r_scope_elem **runp = imap->l_scope;
	  size_t cnt = 0;

	  while (*runp != NULL)
	    {
	      ++cnt;
	      ++runp;
	    }

	  if (*runp != NULL)
	    /* Avoid duplicates.  */
	    continue;

	  if (__builtin_expect (cnt + 1 >= imap->l_scope_max, 0))
	    {
	      /* The 'r_scope' array is too small.  Allocate a new one
		 dynamically.  */
	      struct r_scope_elem **newp;
	      size_t new_size = imap->l_scope_max * 2;

	      if (imap->l_scope == imap->l_scope_mem)
		{
		  newp = (struct r_scope_elem **)
		    malloc (new_size * sizeof (struct r_scope_elem *));
		  if (newp == NULL)
		    _dl_signal_error (ENOMEM, "dlopen", NULL,
				      N_("cannot create scope list"));
		  imap->l_scope = memcpy (newp, imap->l_scope,
					  cnt * sizeof (imap->l_scope[0]));
		}
	      else
		{
		  newp = (struct r_scope_elem **)
		    realloc (imap->l_scope,
			     new_size * sizeof (struct r_scope_elem *));
		  if (newp == NULL)
		    _dl_signal_error (ENOMEM, "dlopen", NULL,
				      N_("cannot create scope list"));
		  imap->l_scope = newp;
		}

	      imap->l_scope_max = new_size;
	    }

	  imap->l_scope[cnt++] = &new->l_searchlist;
	  imap->l_scope[cnt] = NULL;
	}
#if USE_TLS
      /* Only add TLS memory if this object is loaded now and
	 therefore is not yet initialized.  */
      else if (! imap->l_init_called
	       /* Only if the module defines thread local data.  */
	       && __builtin_expect (imap->l_tls_blocksize > 0, 0))
	{
	  /* Now that we know the object is loaded successfully add
	     modules containing TLS data to the slot info table.  We
	     might have to increase its size.  */
	  _dl_add_to_slotinfo (imap);

	  if (imap->l_need_tls_init)
	    {
	      imap->l_need_tls_init = 0;
# ifdef SHARED
	      /* Update the slot information data for at least the
		 generation of the DSO we are allocating data for.  */
	      _dl_update_slotinfo (imap->l_tls_modid);
# endif

	      GL(dl_init_static_tls) (imap);
	      assert (imap->l_need_tls_init == 0);
	    }

	  /* We have to bump the generation counter.  */
	  any_tls = true;
	}
#endif
    }

#if USE_TLS
  /* Bump the generation number if necessary.  */
  if (any_tls && __builtin_expect (++GL(dl_tls_generation) == 0, 0))
    _dl_fatal_printf (N_("\
TLS generation counter wrapped!  Please report this."));
#endif

  /* Run the initializer functions of new objects.  */
  _dl_init (new, args->argc, args->argv, args->env);

  /* Now we can make the new map available in the global scope.  */
  if (mode & RTLD_GLOBAL)
    /* Move the object in the global namespace.  */
    if (add_to_global (new) != 0)
      /* It failed.  */
      return;

  /* Mark the object as not deletable if the RTLD_NODELETE flags was
     passed.  */
  if (__builtin_expect (mode & RTLD_NODELETE, 0))
    new->l_flags_1 |= DF_1_NODELETE;

#ifndef SHARED
  /* We must be the static _dl_open in libc.a.  A static program that
     has loaded a dynamic object now has competition.  */
  __libc_multiple_libcs = 1;
#endif

  /* Let the user know about the opencount.  */
  if (__builtin_expect (GLRO(dl_debug_mask) & DL_DEBUG_FILES, 0))
    _dl_debug_printf ("opening file=%s [%lu]; direct_opencount=%u\n\n",
		      new->l_name, new->l_ns, new->l_direct_opencount);
}


void *
_dl_open (const char *file, int mode, const void *caller_dlopen, Lmid_t nsid,
	  int argc, char *argv[], char *env[])
{
  if ((mode & RTLD_BINDING_MASK) == 0)
    /* One of the flags must be set.  */
    _dl_signal_error (EINVAL, file, NULL, N_("invalid mode for dlopen()"));

  /* Make sure we are alone.  */
  __rtld_lock_lock_recursive (GL(dl_load_lock));

  if (nsid == LM_ID_NEWLM)
    {
      /* Find a new namespace.  */
      for (nsid = 1; nsid < DL_NNS; ++nsid)
	if (GL(dl_ns)[nsid]._ns_loaded == NULL)
	  break;

      if (nsid == DL_NNS)
	{
	  /* No more namespace available.  */
	  __rtld_lock_unlock_recursive (GL(dl_load_lock));

	  _dl_signal_error (EINVAL, file, NULL, N_("\
no more namespaces available for dlmopen()"));
	}

      _dl_debug_initialize (0, nsid)->r_state = RT_CONSISTENT;
    }
  /* Never allow loading a DSO in a namespace which is empty.  Such
     direct placements is only causing problems.  Also don't allow
     loading into a namespace used for auditing.  */
  else if (nsid != LM_ID_BASE && nsid != __LM_ID_CALLER
	   && (GL(dl_ns)[nsid]._ns_nloaded == 0
	       || GL(dl_ns)[nsid]._ns_loaded->l_auditing))
    _dl_signal_error (EINVAL, file, NULL,
		      N_("invalid target namespace in dlmopen()"));

  struct dl_open_args args;
  args.file = file;
  args.mode = mode;
  args.caller_dlopen = caller_dlopen;
  args.caller_dl_open = RETURN_ADDRESS (0);
  args.map = NULL;
  args.nsid = nsid;
  args.argc = argc;
  args.argv = argv;
  args.env = env;

  const char *objname;
  const char *errstring;
  bool malloced;
  int errcode = _dl_catch_error (&objname, &errstring, &malloced,
				 dl_open_worker, &args);

#ifndef MAP_COPY
  /* We must munmap() the cache file.  */
  _dl_unload_cache ();
#endif

  /* Release the lock.  */
  __rtld_lock_unlock_recursive (GL(dl_load_lock));

  if (__builtin_expect (errstring != NULL, 0))
    {
      /* Some error occurred during loading.  */
      char *local_errstring;
      size_t len_errstring;

      /* Remove the object from memory.  It may be in an inconsistent
	 state if relocation failed, for example.  */
      if (args.map)
	{
#ifdef USE_TLS
	  /* Maybe some of the modules which were loaded use TLS.
	     Since it will be removed in the following _dl_close call
	     we have to mark the dtv array as having gaps to fill the
	     holes.  This is a pessimistic assumption which won't hurt
	     if not true.  There is no need to do this when we are
	     loading the auditing DSOs since TLS has not yet been set
	     up.  */
	  if ((mode & __RTLD_AUDIT) == 0)
	    GL(dl_tls_dtv_gaps) = true;
#endif

	  _dl_close (args.map);
	}

      /* Make a local copy of the error string so that we can release the
	 memory allocated for it.  */
      len_errstring = strlen (errstring) + 1;
      if (objname == errstring + len_errstring)
	{
	  size_t total_len = len_errstring + strlen (objname) + 1;
	  local_errstring = alloca (total_len);
	  memcpy (local_errstring, errstring, total_len);
	  objname = local_errstring + len_errstring;
	}
      else
	{
	  local_errstring = alloca (len_errstring);
	  memcpy (local_errstring, errstring, len_errstring);
	}

      if (malloced)
	free ((char *) errstring);

      assert (_dl_debug_initialize (0, args.nsid)->r_state == RT_CONSISTENT);

      /* Reraise the error.  */
      _dl_signal_error (errcode, objname, NULL, local_errstring);
    }

  assert (_dl_debug_initialize (0, args.nsid)->r_state == RT_CONSISTENT);

#ifndef SHARED
  DL_STATIC_INIT (args.map);
#endif

  return args.map;
}


#ifdef SCOPE_DEBUG
#include <unistd.h>

static void
show_scope (struct link_map *new)
{
  int scope_cnt;

  for (scope_cnt = 0; new->l_scope[scope_cnt] != NULL; ++scope_cnt)
    {
      char numbuf[2];
      unsigned int cnt;

      numbuf[0] = '0' + scope_cnt;
      numbuf[1] = '\0';
      _dl_printf ("scope %s:", numbuf);

      for (cnt = 0; cnt < new->l_scope[scope_cnt]->r_nlist; ++cnt)
	if (*new->l_scope[scope_cnt]->r_list[cnt]->l_name)
	  _dl_printf (" %s", new->l_scope[scope_cnt]->r_list[cnt]->l_name);
	else
	  _dl_printf (" <main>");

      _dl_printf ("\n");
    }
}
#endif
