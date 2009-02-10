#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

DIE=0

(test -f $srcdir/configure.in) || {
    echo -n "Error: Directory "\`$srcdir\'" does not look like the"
    echo " top-level package directory"
    exit 1
}
(autoconf --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: You must have 'autoconf' installed."
  echo "Download the appropriate package for your distribution,"
  echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
  exit 1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: You must have 'automake' installed."
  echo "Download the appropriate package for your distribution,"
  echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
  exit 1
}

(aclocal --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "Error: Missing 'aclocal'.  The version of 'automake'"
  echo "installed doesn't appear recent enough."
  echo "Download the appropriate package for your distribution,"
  echo "or get the source tarball at ftp://ftp.gnu.org/pub/gnu/"
  exit 1
}

echo "Creating scripts..."

echo "  aclocal..."
rm -f aclocal.m4
aclocal

echo "  autoheader..."
autoheader

echo "  automake..."
automake --add-missing --copy

echo "  autoconf..."
autoconf

echo "Done."
echo "Run ./configure to set details about the build,"


