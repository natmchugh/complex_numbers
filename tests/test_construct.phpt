--TEST--
Test the Complex Number construtor
--FILE--
<?php
$complexNumber = new ComplexNumber(1.1,2.2);
var_dump($complexNumber);
--EXPECTF--
object(ComplexNumber)#1 (2) {
  ["real"]=>
  float(1.1)
  ["imaginary"]=>
  float(2.2)
}
