/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Virink <virink@outlook.com>                                  |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_PHPJIAMI_DECODE_H
#define PHP_PHPJIAMI_DECODE_H

extern zend_module_entry phpjiami_decode_module_entry;
#define phpext_phpjiami_decode_ptr &phpjiami_decode_module_entry

#define PHP_PHPJIAMI_DECODE_VERSION "0.1.0"
#define PHP_PHPJIAMI_DECODE_AUTHOR "Virink <virink@outlook.com>"

#ifdef PHP_WIN32
#	define PHP_PHPJIAMI_DECODE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PHPJIAMI_DECODE_API __attribute__ ((visibility("default")))
#else
#	define PHP_PHPJIAMI_DECODE_API
#endif

#define PEX(element) execute_data->element

#ifdef ZTS
#include "TSRM.h"
#endif

#ifdef ZTS
#define PHPJIAMI_DECODE_G(v) TSRMG(phpjiami_decode_globals_id, zend_phpjiami_decode_globals *, v)
#else
#define PHPJIAMI_DECODE_G(v) (phpjiami_decode_globals.v)
#endif

#endif
