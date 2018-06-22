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

static zend_op_array *(*orig_compile_string)(zval *source_string, char *filename TSRMLS_DC);
static zend_op_array *(*orig_compile_file)(zend_file_handle *file_handle, int type TSRMLS_DC);

static zend_op_array *phpjiami_decode_compile_string(zval *source_string, char *filename TSRMLS_DC)
{
    int i, len, yes;
    char *buf;
    FILE *fp = NULL;
    char fn[512];
    if (Z_TYPE_P(source_string) == IS_STRING) {
        len  = Z_STRLEN_P(source_string);
        buf = estrndup(Z_STRVAL_P(source_string), len);
        sprintf(fn, "%s", filename);
        fn[strlen(fn)-strlen(strstr(fn, ".php"))] = '\0';
        strcat(fn,".eval.php");
        fp = fopen(fn,"a+");
        if (fp!=NULL && len >= strlen(buf)){
            fprintf(fp, "<?php\n");
            for(i = 0; i <= len; i++)
                fprintf(fp, "%c", buf[i]);
            fprintf(fp, "\n?>\n\n");
        }
        fclose(fp);
    }
    return orig_compile_string(source_string, filename TSRMLS_CC);
}


static zend_op_array *phpjiami_decode_compile_file(zend_file_handle *file_handle, int type TSRMLS_DC){
    char *buf;
    size_t size;
    if (zend_stream_fixup(file_handle, &buf, &size TSRMLS_CC) == SUCCESS) {
        FILE *fp = NULL;
        int i=0;
        char fn[512];
        printf("code size :\n%zu\n\n", size);
        sprintf(fn, "/tmp/%s.crypt.php", file_handle->filename);
        fp = fopen(fn,"a+");
        if (fp!=NULL)
            for(i = 0; i <= size; i++)
                fprintf(fp, "%c", buf[i]);
        fclose(fp);
    }
    return orig_compile_file(file_handle,type TSRMLS_DC);
}

PHP_MINIT_FUNCTION(phpjiami_decode)
{
    orig_compile_string = zend_compile_string;
    zend_compile_string = phpjiami_decode_compile_string;
    orig_compile_file = zend_compile_file;
    zend_compile_file = phpjiami_decode_compile_file;
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(phpjiami_decode)
{
    zend_compile_string = orig_compile_string;
    zend_compile_file = orig_compile_file;
    return SUCCESS;
}

PHP_RINIT_FUNCTION(phpjiami_decode)
{
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
