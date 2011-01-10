--TEST--
Test the Complex Number construtor
--FILE--
<?php
$complexNumber = new ComplexNumber(-1.1,2.2);
var_dump($complexNumber->lessThanTwo());
$complexNumber = new ComplexNumber(-1.1,0.2);
var_dump($complexNumber->lessThanTwo());
--EXPECTF--
bool(false)
bool(true)
