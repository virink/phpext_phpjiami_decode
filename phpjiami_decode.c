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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_phpjiami_decode.h"

static int flag;
static char fn[512];

static zend_op_array *(*orig_compile_string)(zval *source_string, char *filename TSRMLS_DC);

void save_file(char *content){
    FILE *decode_file = NULL;
    sprintf(fn, "%s", zend_get_executed_filename(TSRMLS_C));
    fn[strlen(fn)-strlen(strstr(fn, ".php"))] = '\0';
    strcat(fn,".virink.php");
    
    if(flag && remove(fn) == 0) 
      flag = 0;
    
    decode_file = fopen(fn,"a+");
    
    if (decode_file!=NULL) {
        fprintf(decode_file, "<?php\n%s\n?>\n\n", content);
    }
    fclose(decode_file);
}

static zend_op_array *phpjiami_decode_compile_string(zval *source_string, char *filename TSRMLS_DC)
{
    int c, len, yes;
    char *content;
    if (Z_TYPE_P(source_string) != IS_STRING) {
        return orig_compile_string(source_string, filename TSRMLS_CC);
    }
    len  = Z_STRLEN_P(source_string);
    content = estrndup(Z_STRVAL_P(source_string), len);
    if (len > strlen(content)) {
        for (c=0; c<len; c++)
            if (content[c] == 0)
                content[c] = '?';
    }

    save_file(content);
    
    return orig_compile_string(source_string, filename TSRMLS_CC);
    
    zend_error(E_ERROR, "phpjiami_decode: script abort due to disallowed eval()");
}


PHP_MINIT_FUNCTION(phpjiami_decode)
{
    orig_compile_string = zend_compile_string;
    zend_compile_string = phpjiami_decode_compile_string;
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(phpjiami_decode)
{
    zend_compile_string = orig_compile_string;
	return SUCCESS;
}

PHP_RINIT_FUNCTION(phpjiami_decode)
{
    flag = 1;
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(phpjiami_decode)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(phpjiami_decode)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "phpjiami_decode support", "enabled");
    php_info_print_table_row( 2, "Version", PHP_PHPJIAMI_DECODE_VERSION);
    php_info_print_table_row( 2, "Author", PHP_PHPJIAMI_DECODE_AUTHOR);
	php_info_print_table_end();
}

const zend_function_entry phpjiami_decode_functions[] = {
	PHP_FE_END
};

zend_module_entry phpjiami_decode_module_entry = {
	STANDARD_MODULE_HEADER,
	"phpjiami_decode",
	phpjiami_decode_functions,
	PHP_MINIT(phpjiami_decode),
	PHP_MSHUTDOWN(phpjiami_decode),
	PHP_RINIT(phpjiami_decode),
	PHP_RSHUTDOWN(phpjiami_decode),
	PHP_MINFO(phpjiami_decode),
	PHP_PHPJIAMI_DECODE_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PHPJIAMI_DECODE
ZEND_GET_MODULE(phpjiami_decode)
#endif
