/* Copyright (C) 2004, 2005, 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 2004.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* This file uses the getaddrinfo code but it compiles it without NSCD
   support.  We just need a few symbol renames.  */
#define __getservbyname_r getservbyname_r
#define __inet_aton inet_aton
#define __getsockname getsockname
#define __socket socket
#define __recvmsg recvmsg
#define __bind bind
#define __sendto sendto
#define __strchrnul strchrnul
#define __getline getline

#include <getaddrinfo.c>

/* Support code.  */
#include <check_pf.c>
#ifdef HAVE_LIBIDN
# include <libidn/idn-stub.c>
#endif

/* Some variables normally defined in libc.  */
service_user *__nss_hosts_database;

#if defined NEED_NETLINK && __ASSUME_NETLINK_SUPPORT == 0
int __no_netlink_support attribute_hidden;
#endif
