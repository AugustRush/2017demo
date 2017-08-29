//
//  BucketSort.swift
//
//  Created by Barbara Rodeker on 4/4/16.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//  associated documentation files (the "Software"), to deal in the Software without restriction, including
//  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
//  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
//  EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
//  AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
//  OR OTHER DEALINGS IN THE SOFTWARE.
//
//

import Foundation

//////////////////////////////////////
// MARK: Main algorithm
//////////////////////////////////////


public func bucketSort<T: Sortable>(elements: [T], distributor: Distributor, sorter: Sorter, buckets: inout [Bucket<T>]) -> [T] {
  for elem in elements {
    distributor.distribute(element: elem, buckets: &buckets)
  }

  var results = [T]()

  for bucket in buckets {
    results += bucket.sort(algorithm: sorter)
  }

  return results
}

//////////////////////////////////////
// MARK: Distributor
//////////////////////////////////////


public protocol Distributor {
  func distribute<T: Sortable>(element: T, buckets: inout [Bucket<T>])
}

/*
 * An example of a simple distribution function that send every elements to
 * the bucket representing the range in which it fits.An
 *
 * If the range of values to sort is 0..<49 i.e, there could be 5 buckets of capacity = 10
 * So every element will be classified by the ranges:
 *
 * -  0 ..< 10
 * - 10 ..< 20
 * - 20 ..< 30
 * - 30 ..< 40
 * - 40 ..< 50
 *
 * By following the formula: element / capacity = #ofBucket
 */
public struct RangeDistributor: Distributor {

  public init() {}

  public func distribute<T: Sortable>(element: T, buckets: inout [Bucket<T>]) {
    let value = element.toInt()
    let bucketCapacity = buckets.first!.capacity

    let bucketIndex = value / bucketCapacity
    buckets[bucketIndex].add(item: element)
  }
}

//////////////////////////////////////
// MARK: Sortable
//////////////////////////////////////

public protocol IntConvertible {
  func toInt() -> Int
}

public protocol Sortable: IntConvertible, Comparable {
}

//////////////////////////////////////
// MARK: Sorter
//////////////////////////////////////

public protocol Sorter {
  func sort<T: Sortable>(items: [T]) -> [T]
}

public struct InsertionSorter: Sorter {

  public init() {}

  public func sort<T: Sortable>(items: [T]) -> [T] {
    var results = items
    for i in 0 ..< results.count {
      var j = i
      while j > 0 && results[j-i] > results[j] {

        let auxiliar = results[i]
        results[i] = results[j]
        results[j] = auxiliar

        j -= 1
      }
    }
    return results
  }
}

//////////////////////////////////////
// MARK: Bucket
//////////////////////////////////////

public struct Bucket<T:Sortable> {
  var elements: [T]
  let capacity: Int

  public init(capacity: Int) {
    self.capacity = capacity
    elements = [T]()
  }

  public mutating func add(item: T) {
    if elements.count < capacity {
      elements.append(item)
    }
  }

  public func sort(algorithm: Sorter) -> [T] {
    return algorithm.sort(items: elements)
  }
}
