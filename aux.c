#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"

void diff_exit(int status)
{
    php_error(E_ERROR, "diff terminated");
}

int diff_printf(const char *format, ...)
{
    va_list args;
    int ret;
    char *buffer;
    int size;
    TSRMLS_FETCH();

    va_start(args, format);
    size = vspprintf(&buffer, 0, format, args);
    ret = PHPWRITE(buffer, size);
    efree(buffer);
    va_end(args);

    return ret;
}

int diff_puts(const char *s)
{
    return diff_printf("%s", s);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 sts=4 fdm=marker
 * vim<600: noet sw=4 sts=4
 */
