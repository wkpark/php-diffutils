#ifndef PHP_DIFFUTILS_H
#define PHP_DIFFUTILS_H 1

#define PHP_DIFFUTILS_VERSION "0.1"
#define PHP_DIFFUTILS_EXTNAME "diffutils"

extern zend_module_entry diffutils_module_entry;
#define phpext_diffutils_ptr &diffutils_module_entry

#ifdef PHP_WIN32
#	define PHP_EXTNAME_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_EXTNAME_API __attribute__ ((visibility("default")))
#else
#	define PHP_EXTNAME_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

//PHP_MINIT_FUNCTION(diffutils);
//PHP_MSHUTDOWN_FUNCTION(diffutils);
//PHP_RINIT_FUNCTION(diffutils);
//PHP_RSHUTDOWN_FUNCTION(diffutils);
PHP_MINFO_FUNCTION(diffutils);

PHP_FUNCTION(gnudiff);

#endif	/* PHP_DIFFUTILS_H */
