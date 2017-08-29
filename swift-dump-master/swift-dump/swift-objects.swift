//
//  swift-function.swift
//  swift-dump
//
//  Copyright © 2016 KJCracks. All rights reserved.
//

import Foundation

extension String {
    func replace(_ string:String, replacement:String) -> String {
        return self.replacingOccurrences(of: string, with: replacement, options: NSString.CompareOptions.literal, range: nil)
    }
    
    func removeWhitespace() -> String {
        return self.replace(" ", replacement: "")
    }
}

extension Dictionary {
    mutating func merge<K, V>(_ dict: [K: V]){
        for (k, v) in dict {
            self.updateValue(v as! Value, forKey: k as! Key)
        }
    }
}

class swift_info {
    var Name: String = ""
    var Type: String = ""
    var Symbol: String = ""
    
    func generate(_ indent: Int) -> String {
        return ""
    }
    
}

class swift_variable: swift_info {
    var getSymbol: String = ""
    var setSymbol: String = ""
    
    
    override func generate(_ indent: Int) -> String {
        let indent = spacingForIndent(indent)
        var declaration = "let"
        var setComment = ""
        if (!setSymbol.isEmpty) {
            //can override variable, hence it's a 'var'
            declaration = "var"
            setComment = indent + "//setSymbol: " + setSymbol + "\n"
        }
        return  indent + "//getSymbol: " + getSymbol + "\n" +
                setComment +
                indent + declaration + " " + Name + ": " + Type + " \n\n"
        
    }
    
}

class swift_class: swift_info {
    var Functions: [swift_function] = []
    var Variables: [swift_variable] = []
    var Prefix: String = ""
    var RelevantSymbols: [String] = []
    
    override func generate(_ indent: Int) -> String {
        var output = ""
        for _variable in Variables {
            output = output + _variable.generate(indent + 1)
            
        }
        for _function in Functions {
            output = output + _function.generate(indent + 1)
        }
        return  "class " + Name + " {\n\n" +
            output + "\n" +
        "}"
    }
    
    fileprivate func getVariables() {
        let pattern = Prefix + "g(.*)"
        let demangled_functions =  get_demangled(RelevantSymbols.filter() {
            $0 =~ pattern
            })
        for (mangled, demangled) in demangled_functions {

            //swift_test.Foo.i.getter : Swift.Int
            var split = demangled.components(separatedBy: ":")
            let _variable = swift_variable()
            var fullNameSplit = split[0].removeWhitespace().components(separatedBy: ".")
            _variable.Name = fullNameSplit[fullNameSplit.count - 2]
            _variable.Type = split.last!.removeWhitespace()
            _variable.getSymbol = mangled
            
            //try to find setter function
            let suffix = mangled.replacingOccurrences(of: Prefix + "g", with: "")
            let setter = Prefix + "s" + suffix
            if (RelevantSymbols.contains(setter)) {
                _variable.setSymbol = setter
            }
            Variables.append(_variable)
            
        }
        
        
    }
    
    fileprivate func getFunctions() {
        
        var pattern = Prefix + "[0-9+](.*)"
        var demangled_functions =  get_demangled(RelevantSymbols.filter() {
            $0 =~ pattern
            })
        pattern = Prefix + "cf(.*)" //constructor functions
        demangled_functions.merge(get_demangled(RelevantSymbols.filter() {
            $0 =~ pattern
            }))
            
        for (mangled, demangled) in demangled_functions {
            //swift_test.Foo.swapTwoValues <A> (inout A, inout A) -> ()
            let fullFunctionName = demangled.components(separatedBy: " ")[0]
            //[0] =  <A> (inout A, inout A)
            //[1] = ()
            let _function = swift_function()
            var split = (demangled as NSString).replacingOccurrences(of: fullFunctionName, with: "").components(separatedBy: "->")
            _function.Arguments = split[0]
            _function.Arguments = String(_function.Arguments.characters.dropFirst()) //remove first spacing
            _function.returnType = split[1]
            _function.returnType = String(_function.returnType.characters.dropFirst()) //remove first spacing
            _function.Name = fullFunctionName.components(separatedBy: ".").last!
            _function.Symbol = mangled
            
            Functions.append(_function)
        }
        
        debugPrint(Functions)
        
    }
    
    
    convenience init(class_prefix: String, class_name: String) {
        self.init()
        
        Prefix = "_TF" + class_prefix
        //"_TFC10swift_test3FooD",
        Name = class_name
        RelevantSymbols = getRelevantSymbols(Prefix)
        NSLog("Symbols %@", RelevantSymbols)
        getFunctions()
        getVariables()
    }
    
    
}


class swift_function: swift_info {
    var Arguments: String = ""
    var returnType: String = ""
    
    
    override func generate(_ indent: Int) -> String {
        var return_statement = " "
        if (returnType != "()") {
            return_statement = "return " + defaultValue(returnType)
        }
        let indent = spacingForIndent(indent)
        return  indent + "// Symbol: " + Symbol + "\n" +
            indent + "func " + Name + Arguments + "-> " + returnType + " { " + return_statement + " }\n\n"
    }
    
    
    func description() -> String {
        return "Arguments: " + Arguments + ", returnType: " + returnType
    }
}
