//
//  main.swift
//  swift-dump

//  Swift rewrite of the original swift-dump by neonichu (https://github.com/neonichu/swift-dump)
//  Copyright © 2016 KJCracks. All rights reserved.
//

import Foundation

var symbols = [String]()


infix operator =~
func =~(string:String, regex:String) -> Bool {
    return string.range(of: regex, options: .regularExpression) != nil
}

func defaultValue(_ return_type: String) -> String {
    switch return_type {
    case "Swift.Int":
        return "0"
    case "Swift.String":
        return "\"\""
    default:
        return return_type + "()"
    }
}

func matchesForRegexInText(_ regex: String!, text: String!) -> [String] {
    
    do {
        let regex = try NSRegularExpression(pattern: regex, options: [])
        let nsString = text as NSString
        let results = regex.matches(in: text,
                                            options: [], range: NSMakeRange(0, nsString.length))
        return results.map { nsString.substring(with: $0.range)}
    } catch let error as NSError {
        print("invalid regex: \(error.localizedDescription)")
        return []
    }
}



func spacingForIndent(_ indent: Int) -> String {
    var space = "   "
    for _ in 0 ..< indent {
        space = space + space
    }
    return space
}


func NSTask_and_output(_ launchPath: String, launchArguments: [String]) -> String {
    let task:Process = Process()
    let pipe:Pipe = Pipe()
    
    task.launchPath = launchPath
    task.arguments = launchArguments
    task.standardOutput = pipe
    task.launch()
    
    let handle = pipe.fileHandleForReading
    let data = handle.readDataToEndOfFile()
    let result_s = NSString(data: data, encoding: String.Encoding.utf8)
    return result_s as! String
    
    
}

func getRelevantSymbols(_ prefix: String) -> [String] {
    return symbols.filter() {
        $0.hasPrefix(prefix)
    }
}


func writeToFile(_ _string: String, file: String) {
    do {
        try _string.write(toFile: file, atomically: true, encoding: String.Encoding.utf8)
    }
    catch {
        print("Error: Can't write dump to file " + file)
    }
}


func get_symbols(_ binary: String) -> [String] {
    let output = NSTask_and_output("/usr/bin/xcrun", launchArguments: ["nm", "-g", binary]);
    var lineArray = [String]()
    output.enumerateLines { (line, stop) -> () in

        let symbol  = line.components(separatedBy: " ").last!
        
        
        if (symbol.characters.count > 0) && (symbol.hasPrefix("__T")) {
            lineArray.append(String(symbol.characters.dropFirst()))
        }
        
    }
    return lineArray
}

func get_demangled(_ mangled_array: [String]) -> [String:String] {
    var demangled = [String:String]()
    for mangled in mangled_array {
        demangled[mangled] = get_demangled(mangled)
    }
    return demangled
}

func get_demangled(_ mangled: String) -> String {
    do {
        return try demangleSwiftName(mangled).description
    }
    catch {
        return ""
    }
   
}

if CommandLine.arguments.count < 2 {
    print("Usage: " + CommandLine.arguments[0] + " [swift_binary]")
    exit(0)
}
let path = CommandLine.arguments[1]
let binary = (path as NSString).lastPathComponent

//only filter symbols that contain the binary's name
symbols = get_symbols(path)
    //.filter() { nil != $0.rangeOfString(binary) }

NSLog("symbols %@", symbols)

let tma_symbols = symbols.filter() {
    $0.hasPrefix("_TMa")
}


for symbol in tma_symbols {
    //_TMaC10swift_test3Foo
    var prefix = symbol.substring(from: symbol.characters.index(symbol.startIndex, offsetBy: 4))
    print("prefix " + prefix)
    var type_name = get_demangled(symbol).components(separatedBy: " ").last
    print("Generating dump for type name " + type_name!)
    let type_char = symbol[symbol.characters.index(symbol.startIndex, offsetBy: 4)]
    switch type_char {
    case "C":
        var _class = swift_class(class_prefix: prefix, class_name: type_name!)
        writeToFile(_class.generate(0), file: type_name! + ".swift")
        break
    
        
    default:
        print("Warning: Unknown type char " + String(type_char))
        break
    }
}



