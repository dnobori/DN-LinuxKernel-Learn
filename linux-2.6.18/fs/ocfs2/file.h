#include "linux/autoconf.h"
/* -*- mode: c; c-basic-offset: 8; -*-
 * vim: noexpandtab sw=8 ts=8 sts=0:
 *
 * file.h
 *
 * Function prototypes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#ifndef OCFS2_FILE_H
#define OCFS2_FILE_H

extern const struct file_operations ocfs2_fops;
extern const struct file_operations ocfs2_dops;
extern struct inode_operations ocfs2_file_iops;
extern struct inode_operations ocfs2_special_file_iops;
struct ocfs2_alloc_context;

enum ocfs2_alloc_restarted {
	RESTART_NONE = 0,
	RESTART_TRANS,
	RESTART_META
};
int ocfs2_do_extend_allocation(struct ocfs2_super *osb,
			       struct inode *inode,
			       u32 clusters_to_add,
			       struct buffer_head *fe_bh,
			       struct ocfs2_journal_handle *handle,
			       struct ocfs2_alloc_context *data_ac,
			       struct ocfs2_alloc_context *meta_ac,
			       enum ocfs2_alloc_restarted *reason);
int ocfs2_setattr(struct dentry *dentry, struct iattr *attr);
int ocfs2_getattr(struct vfsmount *mnt, struct dentry *dentry,
		  struct kstat *stat);

int ocfs2_set_inode_size(struct ocfs2_journal_handle *handle,
			 struct inode *inode,
			 struct buffer_head *fe_bh,
			 u64 new_i_size);

#endif /* OCFS2_FILE_H */
