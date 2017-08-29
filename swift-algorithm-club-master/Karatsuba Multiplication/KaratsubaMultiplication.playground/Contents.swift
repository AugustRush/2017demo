//: Playground - noun: a place where people can play

import Foundation

precedencegroup ExponentiativePrecedence {
  higherThan: MultiplicationPrecedence
  lowerThan: BitwiseShiftPrecedence
  associativity: left
}

infix operator ^^: ExponentiativePrecedence
func ^^ (radix: Int, power: Int) -> Int {
  return Int(pow(Double(radix), Double(power)))
}

// Long Multiplication - O(n^2)
func multiply(_ num1: Int, by num2: Int, base: Int = 10) -> Int {
  let num1Array = String(num1).characters.reversed().map{ Int(String($0))! }
  let num2Array = String(num2).characters.reversed().map{ Int(String($0))! }
  
  var product = Array(repeating: 0, count: num1Array.count + num2Array.count)

  for i in num1Array.indices {
    var carry = 0
    for j in num2Array.indices {
      product[i + j] += carry + num1Array[i] * num2Array[j]
      carry = product[i + j] / base
      product[i + j] %= base
    }
    product[i + num2Array.count] += carry
  }
  
  return Int(product.reversed().map{ String($0) }.reduce("", +))!
}

// Karatsuba Multiplication - O(n^log2(3))
func karatsuba(_ num1: Int, by num2: Int) -> Int {
  let num1Array = String(num1).characters
  let num2Array = String(num2).characters
  
  guard num1Array.count > 1 && num2Array.count > 1 else {
    return multiply(num1, by: num2)
  }
  
  let n = max(num1Array.count, num2Array.count)
  let nBy2 = n / 2
  
  let a = num1 / 10^^nBy2
  let b = num1 % 10^^nBy2
  let c = num2 / 10^^nBy2
  let d = num2 % 10^^nBy2
  
  let ac = karatsuba(a, by: c)
  let bd = karatsuba(b, by: d)
  let adPlusbc = karatsuba(a+b, by: c+d) - ac - bd
  
  let product = ac * 10^^(2 * nBy2) + adPlusbc * 10^^nBy2 + bd
  
  return product
}
