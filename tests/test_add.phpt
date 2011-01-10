--TEST--
Test the Complex Number construtor
--FILE--
<?php
$complexNumber = new ComplexNumber(-1.1,2.2);
$complexNumber->add(new ComplexNumber(3.3, 4.4));
var_dump($complexNumber);
--EXPECTF--
object(ComplexNumber)#1 (2) {
  ["real"]=>
  float(2.2)
  ["imaginary"]=>
  float(6.6)
}
