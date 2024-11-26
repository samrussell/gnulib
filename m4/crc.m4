# crc.m4
# serial 4
dnl Copyright (C) 2024 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

# For use by maintainer's after gl_EARLY in configure.ac.
AC_DEFUN([gl_DISABLE_CRC_SLICE_BY_8],
[
  gl_crc_slice_by_8=no
])

AC_DEFUN([gl_CRC_SLICE_BY_8],
[
  AC_MSG_CHECKING([whether to enable CRC slice-by-8 algorithm])
  if test x"$gl_crc_slice_by_8" != x"no"; then
      AC_MSG_RESULT([yes])
      AC_DEFINE([GL_CRC_SLICE_BY_8], [1],
                [Define to get faster but larger CRC32 operation.])
  else
      AC_MSG_RESULT([no])
  fi
])

AC_DEFUN([gl_CRC_PCLMUL],
[
  ac_save_CFLAGS=$CFLAGS
  CFLAGS="-mavx -mpclmul $CFLAGS"
  AC_MSG_CHECKING([if pclmul intrinsic exists])
  AC_CACHE_VAL([gl_cv_crc_pclmul],[
  AC_LINK_IFELSE(
    [AC_LANG_SOURCE([[
      #include <x86intrin.h>

      int
      main (void)
      {
        __m128i a, b;
        a = _mm_clmulepi64_si128 (a, b, 0x00);
        a = _mm_shuffle_epi8 (a, b);
        return __builtin_cpu_supports ("pclmul");
      }
    ]])
    ],[
      gl_cv_crc_pclmul=yes
    ],[
      gl_cv_crc_pclmul=no
    ])])
  AC_MSG_RESULT([$gl_cv_crc_pclmul])
  if test $gl_cv_crc_pclmul = yes; then
    AC_DEFINE([GL_CRC_PCLMUL], [1],
              [CRC32 calculation by pclmul hardware instruction enabled])
  fi
  AM_CONDITIONAL([GL_CRC_PCLMUL],
                [test $gl_cv_crc_pclmul = yes])
  CFLAGS=$ac_save_CFLAGS
])
