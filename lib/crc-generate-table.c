/* crc-generate-table.c -- cyclic redundancy check table generator
   Copyright (C) 2024 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Sam Russell. */

#include <stdio.h>

/*
 * The following function was extracted from RFC 1952 by Sam
 * Russell.  It was modified to remove the reference to the
 * crc_table_computed flag, to extend it to accept a variable number
 * of bits (described below), and reformatted to follow GNU
 * formatting guidelines.
 *
 * make_crc_table() takes a number of bits and generates a lookup
 * table for the CRC32 algorithm. Usage is as follows:
 *
 * make_crc_table(8) : generate for CRC32(0x00) to CRC32(0xFF)
 * make_crc_table(16) : generate for CRC32(0x0000) to CRC32 (0xFF00)
 * in increments of 0x100
 *
 * This is used for the Sarwate algorithm specified in RFC 1952
 * which uses a single lookup table of make_crc_table(8), and for
 * the slice-by-8 algorithm which uses 8 tables from in 8-bit
 * increments from make_crc_table(8) to make_crc_table(64)
 */
unsigned long crc_table[256];

void make_crc_table(int bits)
{
    unsigned long c;

    int n, k;
    for (n = 0; n < 256; n++)
      {
        c = (unsigned long) n;
        for (k = 0; k < bits; k++)
          {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
          }
        crc_table[n] = c;
      }
}

void print_crc_table(int bits)
{
    make_crc_table(bits);

    printf("  {");

    for (int i = 0; i < 256; i++)
      {
        if ((i % 6) == 0)
            printf("\n   ");
        if (i != 255)
            printf(" 0x%08X,", crc_table[i]);
        else
            printf(" 0x%08X\n", crc_table[i]);
      }

    printf("  }");
}

int main(int argc, char* argv[])
{
    printf("static const uint32_t crc32_sliceby8_table[][256] = {\n");
    for (int i=8; i <= 64; i += 8)
      {
        print_crc_table(i);
        if (i < 64)
            printf(",");
        printf("\n");
      }
    printf("};\n");
}
