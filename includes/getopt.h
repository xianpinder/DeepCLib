/* Declarations for getopt.
   Copyright (C) 1989-2026 Free Software Foundation, Inc.

   NOTE: The canonical source of this file is maintained with the GNU C Library.
   Bugs can be reported to bug-glibc@gnu.org.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301,
   USA.  */

#ifndef _GETOPT_H
#define _GETOPT_H

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;

struct option
{
  const char *name;
  int has_arg;
  int *flag;
  int val;
};

#define	no_argument			0
#define required_argument	1
#define optional_argument	2

int getopt (int argc, char *const *argv, const char *optstring);

int __posix_getopt (int argc, char *const *argv, const char *optstring);

int getopt_long (int argc, char **argv, const char *options, const struct option *long_options, int *opt_index);

int getopt_long_only (int argc, char **argv, const char *options, const struct option *long_options, int *opt_index);

/* Internal only.  Users should not call this directly.  */
int _getopt_internal (int argc, char **argv, const char *optstring,
					  const struct option *longopts, int *longind, int long_only,
					  int posixly_correct);
#endif
