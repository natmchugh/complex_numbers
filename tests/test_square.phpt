--TEST--
Test the Complex Number construtor
--FILE--
<?php
$complexNumber = new ComplexNumber(-1.1,2.2);
$complexNumber->square();
var_dump($complexNumber);
--EXPECTF--
object(ComplexNumber)#1 (2) {
  ["real"]=>
  float(-3.63)
  ["imaginary"]=>
  float(-4.84)
}
