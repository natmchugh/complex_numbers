dnl
dnl $Id $
dnl 

PHP_ARG_ENABLE(complex_numbers, whether to enable the complex number extension,
[  --enable-complex_number       Enable complex number support])

if test "$COMPLEX_NUMBERS" != "no"; then
 PHP_NEW_EXTENSION(complex_numbers, complex_numbers.c, $ext_shared)
fi
