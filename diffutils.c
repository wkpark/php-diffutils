/*
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: wkpark at kldp.org 2015/05/02                                |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_diffutils.h"

PHPAPI char *php_trim(char *c, int len, char *what, int what_len, zval *return_value, int mode TSRMLS_DC);

static zend_function_entry diffutils_functions[] = {
    PHP_FE(gnudiff, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry diffutils_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_DIFFUTILS_EXTNAME,
    diffutils_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MINFO(diffutils),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_DIFFUTILS_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DIFFUTILS
ZEND_GET_MODULE(diffutils)
#endif

PHP_FUNCTION(gnudiff)
{
    zval*** args;
    int argc, i, len;
    char *argv[11];
    char *tmp = NULL;

    /* simple check. no more than 10 args */
    if (ZEND_NUM_ARGS() > 10) {
	WRONG_PARAM_COUNT;
    }

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "*", &args, &argc) == FAILURE) {
	RETURN_NULL();
    }

    argv[0] = "diff";
    for (i = 0; i < ZEND_NUM_ARGS(); ++i) {
	convert_to_string_ex(args[i]);
	tmp = php_trim(Z_STRVAL_PP(args[i]), Z_STRLEN_PP(args[i]), NULL, 0, NULL, 3 TSRMLS_CC);
	argv[i + 1] = tmp;
    }

    len = i + 1;
    // call diff
    diffMain(len, argv);

    // free
    if (ZEND_NUM_ARGS() > 0)
	efree(args);
    // php_trim(s, s, NULL, NULL, 3) calls estrndup()
    for (i = 0; i < ZEND_NUM_ARGS(); ++i)
	efree(argv[i + 1]);
}

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(diffutils)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "diffutils support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 sts=4 fdm=marker
 * vim<600: noet sw=4 sts=4
 */
