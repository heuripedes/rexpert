#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(rexpert, 0.1, https://bugs.launchpad.net/rexpert)
AM_INIT_AUTOMAKE(rexpert, 0.1)
AC_CONFIG_SRCDIR([src/rexpert.h])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h locale.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST

# Checks for library functions.

# Checks for packages
gtk_modules="gtk+-2.0 >= 2.10.0"
PKG_CHECK_MODULES(GTK, [$gtk_modules])
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

glib_modules="glib-2.0 >= 2.10.0"
PKG_CHECK_MODULES(glib, [$gtk_modules])
AC_SUBST(glib_CFLAGS)
AC_SUBST(glib_LIBS)

pcre_modules="gtk+-2.0 >= 2.6.0"
PKG_CHECK_MODULES(pcre, [$gtk_modules])
AC_SUBST(pcre_CFLAGS)
AC_SUBST(pcre_LIBS)

AC_OUTPUT(Makefile src/Makefile)
