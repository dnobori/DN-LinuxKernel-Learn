/* Internal header for parsing printf format strings.
   Copyright (C) 1995-1999, 2000, 2002, 2003 Free Software Foundation, Inc.
   This file is part of th GNU C Library.

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

#include <printf.h>
#include <stdint.h>
#include <stddef.h>


struct printf_spec
  {
    /* Information parsed from the format spec.  */
    struct printf_info info;

    /* Pointers into the format string for the end of this format
       spec and the next (or to the end of the string if no more).  */
    const UCHAR_T *end_of_fmt, *next_fmt;

    /* Position of arguments for precision and width, or -1 if `info' has
       the constant value.  */
    int prec_arg, width_arg;

    int data_arg;		/* Position of data argument.  */
    int data_arg_type;		/* Type of first argument.  */
    /* Number of arguments consumed by this format specifier.  */
    size_t ndata_args;
  };


/* The various kinds off arguments that can be passed to printf.  */
union printf_arg
  {
    wchar_t pa_wchar;
    int pa_int;
    long int pa_long_int;
    long long int pa_long_long_int;
    unsigned int pa_u_int;
    unsigned long int pa_u_long_int;
    unsigned long long int pa_u_long_long_int;
    double pa_double;
    long double pa_long_double;
    const char *pa_string;
    const wchar_t *pa_wstring;
    void *pa_pointer;
  };


#ifndef DONT_NEED_READ_INT
/* Read a simple integer from a string and update the string pointer.
   It is assumed that the first character is a digit.  */
static unsigned int
read_int (const UCHAR_T * *pstr)
{
  unsigned int retval = **pstr - L_('0');

  while (ISDIGIT (*++(*pstr)))
    {
      retval *= 10;
      retval += **pstr - L_('0');
    }

  return retval;
}
#endif


/* These are defined in reg-printf.c.  */
extern printf_arginfo_function **__printf_arginfo_table attribute_hidden;
extern printf_function **__printf_function_table attribute_hidden;


/* Find the next spec in FORMAT, or the end of the string.  Returns
   a pointer into FORMAT, to a '%' or a '\0'.  */
extern const unsigned char *__find_specmb (const UCHAR_T *format,
					   mbstate_t *ps) attribute_hidden;

extern const unsigned int *__find_specwc (const UCHAR_T *format)
     attribute_hidden;


/* FORMAT must point to a '%' at the beginning of a spec.  Fills in *SPEC
   with the parsed details.  POSN is the number of arguments already
   consumed.  At most MAXTYPES - POSN types are filled in TYPES.  Return
   the number of args consumed by this spec; *MAX_REF_ARG is updated so it
   remains the highest argument index used.  */
extern size_t __parse_one_specmb (const unsigned char *format, size_t posn,
				  struct printf_spec *spec,
				  size_t *max_ref_arg, mbstate_t *ps)
     attribute_hidden;

extern size_t __parse_one_specwc (const unsigned int *format, size_t posn,
				  struct printf_spec *spec,
				  size_t *max_ref_arg) attribute_hidden;
