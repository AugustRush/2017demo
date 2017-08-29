//: Playground - noun: a place where people can play

import Foundation

/**
 Validate that a string is a plaindrome
 - parameter str: The string to validate
 - returns: `true` if string is plaindrome, `false` if string is not
 */
func isPalindrome(_ str: String) -> Bool {
    let strippedString = str.replacingOccurrences(of: "\\W", with: "", options: .regularExpression, range: nil)
    let length = strippedString.characters.count
    
    if length > 1 {
        return palindrome(strippedString.lowercased(), left: 0, right: length - 1)
    }
    return false
}

/**
 Compares a strings left side character against right side character following
 - parameter str: The string to compare characters of
 - parameter left: Index of left side to compare, must be less than or equal to right
 - parameter right: Index of right side to compare, must be greater than or equal to left
 - returns: `true` if left side and right side have all been compared and they all match, `false` if a left and right aren't equal
 */
private func palindrome(_ str: String, left: Int, right: Int) -> Bool {
    if left >= right {
        return true
    }
    
    let lhs = str[str.index(str.startIndex, offsetBy: left)]
    let rhs = str[str.index(str.startIndex, offsetBy: right)]
    
    if lhs != rhs {
        return false
    }
    
    return palindrome(str, left: left + 1, right: right - 1)
}

//true
isPalindrome("A man, a plan, a canal, Panama!")
isPalindrome("abbcbba")
isPalindrome("racecar")
isPalindrome("Madam, I'm Adam")
isPalindrome("Madam in Eden, I'm Adam")
isPalindrome("Never odd or even")
isPalindrome("5885")
isPalindrome("5 8 8 5")
isPalindrome("58 85")
isPalindrome("৯৯")
isPalindrome("In girum imus nocte et consumimur igni")

// false
isPalindrome("\\\\")
isPalindrome("desserts")
isPalindrome("😀😀")
isPalindrome("")
isPalindrome("a")
isPalindrome("power")
