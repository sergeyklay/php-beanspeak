/*
 * This file is part of the beanspeak extension for PHP.
 *
 * (c) Serghei Iakovlev <sadhooklay@gmail.com>
 *
 * For the full copyright and license information, please view
 * the LICENSE file that was distributed with this source code.
 */

#ifdef HAVE_CONFIG_H
# include "../config.h"
#endif

#include <php.h>
#include <Zend/zend_exceptions.h>
#include <ext/spl/spl_exceptions.h>

#include "../php_beanspeak.h"
#include "exception.h"

zend_class_entry *beanspeak_exceptioninterface_ce_ptr;
zend_class_entry *beanspeak_invalidargumentexception_ce_ptr;

zend_class_entry*
exception_ce(beanspeak_exception_type_t type)
{
	switch (type) {
		default:
		case INVALID_ARGUMENT:
			return beanspeak_invalidargumentexception_ce_ptr;
	}
}

zend_object*
throw_exception(beanspeak_exception_type_t type, const char *fmt, ...)
{
	char *msg;
	zend_object *exception;
	va_list argv;

	va_start(argv, fmt);
	vspprintf(&msg, 0, fmt, argv);
	va_end(argv);

	exception = zend_throw_exception(exception_ce(type), msg, type);
	efree(msg);

	return exception;
}

/* {{{ beanspeak_init_exception_iface
 * Create and register 'Beanspeak\Exception\ExceptionInterface' interface. */
int beanspeak_init_exception_iface(INIT_FUNC_ARGS) {
	BEANSPEAK_REGISTER_CLASS(Beanspeak\\Exception, ExceptionInterface, beanspeak,
		exceptioninterface, beanspeak_exception_method_entry, ZEND_ACC_INTERFACE);

	zend_class_implements(beanspeak_exceptioninterface_ce_ptr, 1, zend_ce_throwable);

	return SUCCESS;
}
/* }}} */

/* {{{ beanspeak_init_args_e
 * Create and register 'Beanspeak\Exception\InvalidArgumentException' class. */
int beanspeak_init_invalid_args_e(INIT_FUNC_ARGS) {
	BEANSPEAK_REGISTER_CLASS_EX(Beanspeak\\Exception, InvalidArgumentException, beanspeak, invalidargumentexception,
		spl_ce_InvalidArgumentException, beanspeak_exception_method_entry, 0);

	zend_class_implements(beanspeak_invalidargumentexception_ce_ptr, 1, beanspeak_exceptioninterface_ce_ptr);

	return SUCCESS;
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
