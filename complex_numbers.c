/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Nathaniel McHugh nat@fishtrap.co.uk			  |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "complex_numbers.h"
#include <math.h>

zend_class_entry *php_complexnumbers_fc_entry;


/* {{{ proto resource festival_say_text()
   Says the passed in text  */
PHP_METHOD(ComplexNumber, add)
{
    zval *objvar;
    zval *thisobjvar = getThis();
	    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O",
								          &objvar, php_complexnumbers_fc_entry) == FAILURE) {
			        RETURN_NULL();

		}
	zval **a;
	if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
					           "real", sizeof("real"), (void **)&a) == FAILURE) {
		    /* $thisobjvar>real doesn't exist */
		    return;
	}
	zval **b;
	if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
	                           "imaginary", sizeof("imaginary"), (void**)&b) == FAILURE) {
			              /* $objvar>imaginary doesn't exist */
	         return;
	}

	zval ** c;
	if (zend_hash_find(Z_OBJPROP_P(objvar),
	                            "real", sizeof("real"), (void**)&c) == FAILURE) {
	          /* $objvar>real doesn't exist */
	          return;
	}
	 zval ** d;
	     if (zend_hash_find(Z_OBJPROP_P(objvar),
	                           "imaginary", sizeof("imaginary"), (void**)&d) == FAILURE) {
	           /* $objvar>imaginary doesn't exist */
	           return;
	}
   add_property_double(thisobjvar, "real", Z_DVAL_PP(a)+Z_DVAL_PP(c));
   add_property_double(thisobjvar, "imaginary", Z_DVAL_PP(b)+Z_DVAL_PP(d));
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto resource festival_say_text()
 *    Says the passed in text  */
PHP_METHOD(ComplexNumber, square)
{
	    zval *thisobjvar = getThis();
					    zval **a;
						    if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
		                                  "real", sizeof("real"), (void **)&a) == FAILURE) {
								            /* $thisobjvar>real doesn't exist */
								            return;
										    }
					    zval **b;
						    if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
		                                  "imaginary", sizeof("imaginary"), (void**)&b) == FAILURE) {
					                          /* $objvar>imaginary
											   * doesn't exist */
										             return;
													     }

						double real = Z_DVAL_PP(a); 
						double imaginary = Z_DVAL_PP(b); 
						 add_property_double(thisobjvar, "real", pow(real, 2) - pow(imaginary, 2) );
						 add_property_double(thisobjvar, "imaginary", 2*real*imaginary);
						 RETURN_TRUE;
}
/* }}} */

/* {{{ proto resource festival_say_text()
 *  *    Says the passed in text  */
PHP_METHOD(ComplexNumber, lessThanTwo)
{
	        zval *thisobjvar = getThis();
			     zval **a;
				                             if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
											"real", sizeof("real"), (void **)&a) == FAILURE) {
												      return;
													   }

	          zval **b;
			                                               if (zend_hash_find(Z_OBJPROP_P(thisobjvar),
											 "imaginary", sizeof("imaginary"), (void **)&b) == FAILURE) {
								                       return;                                                                                
								                       }
						double real = Z_DVAL_PP(a); 
						double imaginary= Z_DVAL_PP(b);
RETVAL_BOOL(real*real+imaginary*imaginary < 4);
}

PHP_METHOD(ComplexNumber, __construct) {
double real = 0;
double imaginary = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &real,  &imaginary) == FAILURE) {
        RETURN_FALSE;
    }
	   zval *objvar = getThis();

	       if (!objvar) {
			           php_error_docref(NULL TSRMLS_CC, E_WARNING,
										                        "Constructor called statically!");
					           RETURN_FALSE;
				       }
		       add_property_double(objvar, "real", real);
			   add_property_double(objvar, "imaginary", imaginary);
}



ZEND_BEGIN_ARG_INFO_EX(complex_numbers_args, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry complex_numbers_functions[] = {
	{NULL, NULL, NULL}
};

PHP_MINFO_FUNCTION(complex_numbers)
{
	char version[256];
	php_info_print_table_start();
	php_info_print_table_header(2, "complex number support", "enabled");
	php_info_print_table_row(2, "version", COMPLEX_NUMBERS_VERSION);
	php_info_print_table_end();
}

#define PHP_COMPLEX_NUMBERS_FC_NAME "ComplexNumber"
static zend_function_entry php_complexnumbers_fc_functions [] = {
/*
      PHP_ME(ComplexNumber, __construct, NULL, ZEND_ACC_PUBLIC)
*/
      PHP_ME(ComplexNumber, add, NULL, ZEND_ACC_PUBLIC)
      PHP_ME(ComplexNumber, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
      PHP_ME(ComplexNumber, square, NULL, ZEND_ACC_PUBLIC)
      PHP_ME(ComplexNumber, lessThanTwo, NULL, ZEND_ACC_PUBLIC)
      {NULL, NULL, NULL}
};

PHP_MINIT_FUNCTION(complex_numbers)
{
      zend_class_entry ce;
      INIT_CLASS_ENTRY(ce, PHP_COMPLEX_NUMBERS_FC_NAME,
                       php_complexnumbers_fc_functions);
      php_complexnumbers_fc_entry =
            zend_register_internal_class(&ce TSRMLS_CC);
      return SUCCESS;
}

zend_module_entry complex_numbers_module_entry = {
	STANDARD_MODULE_HEADER,
	"complex_numbers",
	complex_numbers_functions,
        PHP_MINIT(complex_numbers), /* MINIT */
        NULL, /* MSHUTDOWN */
	NULL,	/* RINIT */
	NULL,   /* RSHUTDOWN */
	PHP_MINFO(complex_numbers),
	COMPLEX_NUMBERS_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_COMPLEX_NUMBERS
ZEND_GET_MODULE(complex_numbers)
#endif
/*
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * End:
 * vim600: fdm=marker
 * vim: sw=4 ts=4 noet
 */
