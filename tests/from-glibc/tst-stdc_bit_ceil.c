/* Test stdc_bit_ceil functions and macros.
   Copyright (C) 2024 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <tst-stdbit.h>

static const struct stdbit_test inputs[] =
  {
    { 0ULL, 0x1, 0x1, 0x1, 0x1ULL },
    { 0x1ULL, 0x1, 0x1, 0x1, 0x1ULL },
    { 0x2ULL, 0x2, 0x2, 0x2, 0x2ULL },
    { 0x3ULL, 0x4, 0x4, 0x4, 0x4ULL },
    { 0x4ULL, 0x4, 0x4, 0x4, 0x4ULL },
    { 0x5ULL, 0x8, 0x8, 0x8, 0x8ULL },
    { 0x6ULL, 0x8, 0x8, 0x8, 0x8ULL },
    { 0x7ULL, 0x8, 0x8, 0x8, 0x8ULL },
    { 0x8ULL, 0x8, 0x8, 0x8, 0x8ULL },
    { 0x9ULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xaULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xbULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xcULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xdULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xeULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0xfULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0x10ULL, 0x10, 0x10, 0x10, 0x10ULL },
    { 0x11ULL, 0x20, 0x20, 0x20, 0x20ULL },
    { 0x12ULL, 0x20, 0x20, 0x20, 0x20ULL },
    { 0x1fULL, 0x20, 0x20, 0x20, 0x20ULL },
    { 0x20ULL, 0x20, 0x20, 0x20, 0x20ULL },
    { 0x7fULL, 0x80, 0x80, 0x80, 0x80ULL },
    { 0x80ULL, 0x80, 0x80, 0x80, 0x80ULL },
    { 0x81ULL, 0, 0x100, 0x100, 0x100ULL },
    { 0x9aULL, 0, 0x100, 0x100, 0x100ULL },
    { 0xf3ULL, 0, 0x100, 0x100, 0x100ULL },
    { 0xffULL, 0, 0x100, 0x100, 0x100ULL },
    { 0x100ULL, 0x1, 0x100, 0x100, 0x100ULL },
    { 0x101ULL, 0x1, 0x200, 0x200, 0x200ULL },
    { 0x102ULL, 0x2, 0x200, 0x200, 0x200ULL },
    { 0x1feULL, 0, 0x200, 0x200, 0x200ULL },
    { 0x1ffULL, 0, 0x200, 0x200, 0x200ULL },
    { 0x200ULL, 0x1, 0x200, 0x200, 0x200ULL },
    { 0x234ULL, 0x40, 0x400, 0x400, 0x400ULL },
    { 0x4567ULL, 0x80, 0x8000, 0x8000, 0x8000ULL },
    { 0x7fffULL, 0, 0x8000, 0x8000, 0x8000ULL },
    { 0x8000ULL, 0x1, 0x8000, 0x8000, 0x8000ULL },
    { 0x8001ULL, 0x1, 0, 0x10000, 0x10000ULL },
    { 0xfffeULL, 0, 0, 0x10000, 0x10000ULL },
    { 0xffffULL, 0, 0, 0x10000, 0x10000ULL },
    { 0x10000ULL, 0x1, 0x1, 0x10000, 0x10000ULL },
    { 0x10001ULL, 0x1, 0x1, 0x20000, 0x20000ULL },
    { 0xfedcba98ULL, 0, 0, 0, 0x100000000ULL },
    { 0xfffffefeULL, 0, 0, 0, 0x100000000ULL },
    { 0xffffffffULL, 0, 0, 0, 0x100000000ULL },
    { 0x100000000ULL, 0x1, 0x1, 0x1, 0x100000000ULL },
    { 0x100000001ULL, 0x1, 0x1, 0x1, 0x200000000ULL },
    { 0x123456789ULL, 0, 0x8000, 0x40000000, 0x200000000ULL },
    { 0x123456789abcdefULL, 0, 0, 0, 0x200000000000000ULL },
    { 0x789abcdef0123456ULL, 0x80, 0x4000, 0, 0x8000000000000000ULL },
    { 0x8000000000000000ULL, 0x1, 0x1, 0x1, 0x8000000000000000ULL },
    { 0x8000000000000001ULL, 0x1, 0x1, 0x1, 0ULL },
    { 0xfffffffffffffffeULL, 0, 0, 0, 0ULL },
    { 0xffffffffffffffffULL, 0, 0, 0, 0ULL },
  };

TEST_STDBIT_SAME_TOPLEVEL (stdc_bit_ceil);

static int
do_test (void)
{
  TEST_STDBIT_SAME (stdc_bit_ceil, inputs);
  return 0;
}

#include <support/test-driver.c>