PHP_ARG_WITH(diffutils, whether to diffutils support,
dnl Make sure that the comment is aligned:
[  --with-diffutils[=path]    Include diffutils support])
if test "$PHP_DIFFUTILS" != "no"; then

  SEARCH_PATH="/usr/local /usr"
  SEARCH_FOR="src/diff.h"
  SEARCH_LIB="libdiffutils"

  dnl search leveldb
  AC_MSG_CHECKING([for diffutils location])
  for i in $PHP_DIFFUTILS $SEARCH_PATH ; do
    if test -r $i/$SEARCH_FOR; then
      DIFFUTILS_INCLUDE_DIR=$i
      AC_MSG_RESULT(diff.h header found in $i)
      diff_c_sources=""
      PHP_DIFFUTILS_CFLAGS=""
    fi

    if test -r $i/src/$SEARCH_LIB.la; then
      DIFFUTILS_LIB_DIR=$i/src
      AC_MSG_RESULT(diffutils lib found in $i/diffutils)
    fi
  done

  if test -z "$DIFFUTILS_INCLUDE_DIR"; then
    AC_MSG_RESULT([diff.h not found])
    AC_MSG_ERROR([Please reinstall the diffutils distribution])
  fi

  if test -z "$DIFFUTILS_LIB_DIR"; then
    AC_MSG_RESULT([libdiff not found])
    AC_MSG_ERROR([Please reinstall the diffutils distribution])
  fi

  # --with-diffutils -> add include path
  PHP_ADD_INCLUDE($DIFFUTILS_INCLUDE_DIR/src)

  # --with-diffutils -> check for lib and symbol presence
  LIBNAME=diffutils
  PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DIFFUTILS_LIB_DIR, DIFFUTILS_SHARED_LIBADD)

  PHP_SUBST(DIFFUTILS_SHARED_LIBADD)
  AM_ENABLE_STATIC()

  AC_DEFINE(HAVE_DIFFUTILS, 1, [Whether you have diffutils])
  PHP_NEW_EXTENSION(diffutils, diffutils.c aux.c $diff_c_sources, $ext_shared,, $PHP_DIFFUTILS_CFLAGS)
fi
