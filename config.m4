dnl $Id$
dnl config.m4 for extension phpjiami_decode

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phpjiami_decode, for phpjiami_decode support,
dnl Make sure that the comment is aligned:
dnl [  --with-phpjiami_decode             Include phpjiami_decode support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(phpjiami_decode, whether to enable phpjiami_decode support,
dnl Make sure that the comment is aligned:
[  --enable-phpjiami_decode           Enable phpjiami_decode support])

if test "$PHP_PHPJIAMI_DECODE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phpjiami_decode -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phpjiami_decode.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPJIAMI_DECODE/$SEARCH_FOR; then # path given as parameter
  dnl   PHPJIAMI_DECODE_DIR=$PHP_PHPJIAMI_DECODE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phpjiami_decode files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPJIAMI_DECODE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPJIAMI_DECODE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phpjiami_decode distribution])
  dnl fi

  dnl # --with-phpjiami_decode -> add include path
  dnl PHP_ADD_INCLUDE($PHPJIAMI_DECODE_DIR/include)

  dnl # --with-phpjiami_decode -> check for lib and symbol presence
  dnl LIBNAME=phpjiami_decode # you may want to change this
  dnl LIBSYMBOL=phpjiami_decode # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPJIAMI_DECODE_DIR/$PHP_LIBDIR, PHPJIAMI_DECODE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPJIAMI_DECODELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phpjiami_decode lib version or lib not found])
  dnl ],[
  dnl   -L$PHPJIAMI_DECODE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PHPJIAMI_DECODE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phpjiami_decode, phpjiami_decode.c, $ext_shared)
fi
