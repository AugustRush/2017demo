//: Playground - noun: a place where people can play

import UIKit

/// Ecode & Decode
struct Person: Codable {
    var name: String
    var address: String
    var age: Int
}

let encoder = JSONEncoder()
let decoder = JSONDecoder()

var person = Person(name: "august", address: "shang-hai", age: 28)

let data = try encoder.encode(person)
let decodePerson = try decoder.decode(Person.self, from: data)

//// Mutile-lines String

let ms = """
    this
    is
    mutiple
    lines
    String
"""

///// keyPath & KVC

let name = person[keyPath: \Person.name]
person[keyPath: \Person.name] = "liupingwei"

let json = String.init(data: try encoder.encode(person), encoding: .utf8)

