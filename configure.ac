#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([ssutils], [0.5.0], [csdevs@ag.com])
AC_CONFIG_SRCDIR([src/yph.c])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Configure headers
AC_CONFIG_HEADERS([config.h])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strchr strspn])

# Configure our includes
AC_SUBST([AM_CPPFLAGS], ['-I$(top_srcdir)/lib'])

# configure our dirs
AC_SUBST([SSU_ASSETS_DIR],['$(pkgdatadir)'])
AC_SUBST([SSU_TMP_DIR],['$(prefix)/temp'])
AC_SUBST([SSU_CACHE_DIR],['$(prefix)/cache'])

# Configure our files
AC_CONFIG_FILES([
 Makefile
 lib/Makefile
 src/Makefile
 assets/Makefile
])

AC_OUTPUT
