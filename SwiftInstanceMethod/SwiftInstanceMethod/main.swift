//
//  main.swift
//  SwiftInstanceMethod
//
//  Created by AugustRush on 2017/5/12.
//  Copyright © 2017年 August. All rights reserved.
//

import Foundation

class ClassA {
    func method1() -> Int {
        return 100
    }
    
    func method2() -> String {
        return "Just test!"
    }
}

// normal
let normal = {
    let a = ClassA()
    let v1 = a.method1()
    let v2 = a.method2()
    print("v1 is \(v1), v2 is \(v2)")
}

// special

let special = {
    let a = ClassA()
    let method1 = ClassA.method1
    let method2 = ClassA.method2
    let v1 = method1(a)()
    let v2 = method2(a)()
    print("v1 is \(v1), v2 is \(v2)")
}

normal()
special()

