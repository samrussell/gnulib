/*
 * Copyright (C) 2005-2007, 2010-2024 Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Simon Josefsson.  */

#include <config.h>

#include "crc.h"

#include <stdio.h>

int
main (int argc, char *argv[])
{
  uint32_t p;

  p = crc32_update_no_xor (42, "foobarbazzbuzz", 14);
  if (p != 0xf0009b19)
    {
      printf ("cunx got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32_no_xor ("foobarbazbuz", 12);
  if (p != 0x7dab8665)
    {
      printf ("cnx got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32_update (42, "foobarbazbuz", 12);
  if (p != 0xf4787393)
    {
      printf ("cu got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32 ("foobarbazbuz", 12);
  if (p != 0x67e400a)
    {
      printf ("c got %lx\n", (unsigned long) p);
      return 1;
    }

  return 0;
}
