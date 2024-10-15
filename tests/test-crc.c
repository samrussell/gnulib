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
#include <string.h>

int
main (int argc, char *argv[])
{
  uint32_t p;
  size_t i;
  char plaintext[] = "Gnulib crc testsGnulib crc tests"
                     "Gnulib crc testsGnulib crc tests"
                     "Gnulib crc testsGnulib crc tests"
                     "Gnulib crc testsGnulib crc tests"
                     "Gnulib crc testsGnulib crc tests";
  char data[sizeof(plaintext) + sizeof(unsigned long int)];

  p = crc32_update_no_xor (42, "foo", 3);
  if (p != 0x46e87f05)
    {
      printf ("cunx got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32_no_xor ("foo", 3);
  if (p != 0x7332bc33)
    {
      printf ("cnx got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32_update (42, "foo", 3);
  if (p != 0xb9a9a617)
    {
      printf ("cu got %lx\n", (unsigned long) p);
      return 1;
    }

  p = crc32 ("foo", 3);
  if (p != 0x8c736521)
    {
      printf ("c got %lx\n", (unsigned long) p);
      return 1;
    }

  /*
   * Test for new CRC32 implementation
   * The original implementation works on a byte-by-byte basis
   * but new implementations may work on 8 or 16 byte alignments.
   * This test will confirm correct operation with non-aligned
   * data.
   */

  for (i = 0; i < sizeof(unsigned long int); i++)
    {
      memcpy(data + i, plaintext, sizeof(plaintext));
      p = crc32_update_no_xor (0, data + i, sizeof(plaintext));
      if (p != 0x654978c3)
        {
          printf ("aligned c at %lu got %lx\n", i, (unsigned long) p);
          return 1;
        }
    }


  return 0;
}
