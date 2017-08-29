# Linked List

A linked list is a sequence of data items, just like an array. But where an array allocates a big block of memory to store the objects, the elements in a linked list are totally separate objects in memory and are connected through links:

	+--------+    +--------+    +--------+    +--------+
	|        |    |        |    |        |    |        |
	| node 0 |--->| node 1 |--->| node 2 |--->| node 3 |
	|        |    |        |    |        |    |        |
	+--------+    +--------+    +--------+    +--------+

The elements of a linked list are referred to as *nodes*. The above picture shows a *singly linked list*, where each node only has a reference -- or a "pointer" -- to the next node. In a *doubly linked list*, shown below, nodes also have pointers to the previous node:

	+--------+    +--------+    +--------+    +--------+
	|        |--->|        |--->|        |--->|        |
	| node 0 |    | node 1 |    | node 2 |    | node 3 |
	|        |<---|        |<---|        |<---|        |
	+--------+    +--------+    +--------+    +--------+

You need to keep track of where the list begins. That's usually done with a pointer called the *head*:

	         +--------+    +--------+    +--------+    +--------+
	head --->|        |--->|        |--->|        |--->|        |---> nil
	         | node 0 |    | node 1 |    | node 2 |    | node 3 |
	 nil <---|        |<---|        |<---|        |<---|        |<--- tail
	         +--------+    +--------+    +--------+    +--------+

It's also useful to have a reference to the end of the list, known as the *tail*. Note that the "next" pointer of the last node is `nil`, just like the "previous" pointer of the very first node.

## Performance of linked lists

Most operations on a linked list have **O(n)** time, so linked lists are generally slower than arrays. However, they are also much more flexible -- rather than having to copy large chunks of memory around as with an array, many operations on a linked list just require you to change a few pointers.

The reason for the **O(n)** time is that you can't simply write `list[2]` to access node 2 from the list. If you don't have a reference to that node already, you have to start at the `head` and work your way down to that node by following the `next` pointers (or start at the `tail` and work your way back using the `previous` pointers).

But once you have a reference to a node, operations like insertion and deletion are really quick. It's just that finding the node is slow.

This means that when you're dealing with a linked list, you should insert new items at the front whenever possible. That is an **O(1)** operation. Likewise for inserting at the back if you're keeping track of the `tail` pointer.

## Singly vs doubly linked lists

A singly linked list uses a little less memory than a doubly linked list because it doesn't need to store all those `previous` pointers.

But if you have a node and you need to find its previous node, you're screwed. You have to start at the head of the list and iterate through the entire list until you get to the right node.

For many tasks, a doubly linked list makes things easier.

## Why use a linked list?

A typical example of where to use a linked list is when you need a [queue](../Queue/). With an array, removing elements from the front of the queue is slow because it needs to shift down all the other elements in memory. But with a linked list it's just a matter of changing `head` to point to the second element. Much faster.

But to be honest, you hardly ever need to write your own linked list these days. Still, it's useful to understand how they work; the principle of linking objects together is also used with [trees](../Tree/) and [graphs](../Graph/).

## The code

We'll start by defining a type to describe the nodes:

```swift
public class LinkedListNode<T> {
  var value: T
  var next: LinkedListNode?
  weak var previous: LinkedListNode?

  public init(value: T) {
    self.value = value
  }
}
```

This is a generic type, so `T` can be any kind of data that you'd like to store in the node. We'll be using strings in the examples that follow.

Ours is a doubly-linked list and each node has a `next` and `previous` pointer. These can be `nil` if there are no next or previous nodes, so these variables must be optionals. (In what follows, I'll point out which functions would need to change if this was just a singly- instead of a doubly-linked list.)

> **Note:** To avoid ownership cycles, we declare the `previous` pointer to be weak. If you have a node `A` that is followed by node `B` in the list, then `A` points to `B` but also `B` points to `A`. In certain circumstances, this ownership cycle can cause nodes to be kept alive even after you deleted them. We don't want that, so we make one of the pointers `weak` to break the cycle.

Let's start building `LinkedList`. Here's the first bit:

```swift
public class LinkedList<T> {
  public typealias Node = LinkedListNode<T>

  private var head: Node?
  
  public var isEmpty: Bool {
    return head == nil
  }
  
  public var first: Node? {
    return head
  }
}
```

Ideally, I'd like to put the `LinkedListNode` class inside `LinkedList` but Swift currently doesn't allow generic types to have nested types. Instead we're using a typealias so inside `LinkedList` we can write the shorter `Node` instead of `LinkedListNode<T>`.

This linked list only has a `head` pointer, not a tail. Adding a tail pointer is left as an exercise for the reader. (I'll point out which functions would be different if we also had a tail pointer.)

The list is empty if `head` is nil. Because `head` is a private variable, I've added the property `first` to return a reference to the first node in the list.

You can try it out in a playground like this:

```swift
let list = LinkedList<String>()
list.isEmpty   // true
list.first     // nil
```

Let's also add a property that gives you the last node in the list. This is where it starts to become interesting:

```swift
  public var last: Node? {
    if var node = head {
      while case let next? = node.next {
        node = next
      }
      return node
    } else {
      return nil
    }
  }
```

If you're new to Swift, you've probably seen `if let` but maybe not `if var`. It does the same thing -- it unwraps the `head` optional and puts the result in a new local variable named `node`. The difference is that `node` is not a constant but an actual variable, so we can change it inside the loop.

The loop also does some Swift magic. The `while case let next? = node.next` bit keeps looping until `node.next` is nil. You could have written this as follows:

```swift
      var node: Node? = head
      while node != nil && node!.next != nil {
        node = node!.next
      }
```

But that doesn't feel very Swifty to me. We might as well make use of Swift's built-in support for unwrapping optionals. You'll see a bunch of these kinds of loops in the code that follows.

> **Note:** If we kept a tail pointer, `last` would simply do `return tail`. But we don't, so it has to step through the entire list from beginning to the end. It's an expensive operation, especially if the list is long.

Of course, `last` only returns nil because we don't have any nodes in the list. Let's add a method that adds a new node to the end of the list:

```swift
  public func append(value: T) {
    let newNode = Node(value: value)
    if let lastNode = last {
      newNode.previous = lastNode
      lastNode.next = newNode
    } else {
      head = newNode
    }
  }
```

The `append()` method first creates a new `Node` object and then asks for the last node using the `last` property we've just added. If there is no such node, the list is still empty and we make `head` point to this new `Node`. But if we did find a valid node object, we connect the `next` and `previous` pointers to link this new node into the chain. A lot of linked list code involves this kind of `next` and `previous` pointer manipulation.

Let's test it in the playground:

```swift
list.append("Hello")
list.isEmpty         // false
list.first!.value    // "Hello"
list.last!.value     // "Hello"
```

The list looks like this:

	         +---------+
	head --->|         |---> nil
	         | "Hello" |
	 nil <---|         |
	         +---------+

Now add a second node:

```swift
list.append("World")
list.first!.value    // "Hello"
list.last!.value     // "World"
```

And the list looks like:

	         +---------+    +---------+
	head --->|         |--->|         |---> nil
	         | "Hello" |    | "World" |
	 nil <---|         |<---|         |
	         +---------+    +---------+

You can verify this for yourself by looking at the `next` and `previous` pointers:

```swift
list.first!.previous          // nil
list.first!.next!.value       // "World"
list.last!.previous!.value    // "Hello"
list.last!.next               // nil
```

Let's add a method to count how many nodes are in the list. This will look very similar to what we did already:

```swift
  public var count: Int {
    if var node = head {
      var c = 1
      while case let next? = node.next {
        node = next
        c += 1
      }
      return c
    } else {
      return 0
    }
  }
```

It loops through the list in the same manner but this time increments a counter as well.

> **Note:** One way to speed up `count` from **O(n)** to **O(1)** is to keep track of a variable that counts how many nodes are in the list. Whenever you add or remove a node, you also update this variable.

What if we wanted to find the node at a specific index in the list? With an array we can just write `array[index]` and it's an **O(1)** operation. It's a bit more involved with linked lists, but again the code follows a similar pattern:

```swift
  public func nodeAt(_ index: Int) -> Node? {
    if index >= 0 {
      var node = head
      var i = index
      while node != nil {
        if i == 0 { return node }
        i -= 1
        node = node!.next
      }
    }
    return nil
  }
```

The loop looks a little different but it does the same thing: it starts at `head` and then keeps following the `node.next` pointers to step through the list. We're done when we've seen `index` nodes, i.e. when the counter has reached 0.

Try it out:

```swift
list.nodeAt(0)!.value    // "Hello"
list.nodeAt(1)!.value    // "World"
list.nodeAt(2)           // nil
```

For fun we can implement a `subscript` method too:

```swift
  public subscript(index: Int) -> T {
    let node = nodeAt(index)
    assert(node != nil)
    return node!.value
  }
```

Now you can write the following:

```swift
list[0]   // "Hello"
list[1]   // "World"
list[2]   // crash!
```

It crashes on `list[2]` because there is no node at that index.

So far we've written code to add new nodes to the end of the list, but that's slow because you need to find the end of the list first. (It would be fast if we used a tail pointer.) For this reason, if the order of the items in the list doesn't matter, you should insert at the front of the list instead. That's always an **O(1)** operation.

Let's write a method that lets you insert a new node at any index in the list. First, we'll define a helper function:

```swift
  private func nodesBeforeAndAfter(index: Int) -> (Node?, Node?) {
    assert(index >= 0)
    
    var i = index
    var next = head
    var prev: Node?

    while next != nil && i > 0 {
      i -= 1
      prev = next
      next = next!.next
    }
    assert(i == 0)

    return (prev, next)
  }
```

This returns a tuple containing the node currently at the specified index and the node that immediately precedes it, if any. The loop is very similar to `nodeAtIndex()`, except that here we also keep track of what the previous node is as we iterate through the list. 

Let's look at an example. Suppose we have the following list:

	head --> A --> B --> C --> D --> E --> nil

We want to find the nodes before and after index 3. As we start the loop, `i = 3`, `next` points at `"A"`, and `prev` is nil. 

	head --> A --> B --> C --> D --> E --> nil
	        next

We decrement `i`, make `prev` point to `"A"`, and move `next` to the next node, `"B"`:

	head --> A --> B --> C --> D --> E --> F --> nil
	        prev  next

Again, we decrement `i` and update the pointers. Now `prev` points to `"B"`, and `next` points to `"C"`:

	head --> A --> B --> C --> D --> E --> F --> nil
	              prev  next

As you can see, `prev` always follows one behind `next`. We do this one more time and then `i` equals 0 and we exit the loop:

	head --> A --> B --> C --> D --> E --> F --> nil
	                    prev  next

The `assert()` after the loop checks whether there really were enough nodes in the list. If `i > 0` at this point, then the specified index was too large.

> **Note:** If any of the loops in this article don't make much sense to you, then draw a linked list on a piece of paper and step through the loop by hand, just like what we did here.

For this example, the function returns `("C", "D")` because `"D"` is the node at index 3 and `"C"` is the one right before that.

Now that we have this helper function, we can write the method for inserting nodes:

```swift
  public func insert(value: T, atIndex index: Int) {
    let (prev, next) = nodesBeforeAndAfter(index)     // 1
    
    let newNode = Node(value: value)    // 2
    newNode.previous = prev
    newNode.next = next
    prev?.next = newNode
    next?.previous = newNode

    if prev == nil {                    // 3
      head = newNode
    }
  }
```

Some remarks about this method:

1. First, we need to find where to insert this node. After calling the helper method, `prev` points to the previous node and `next` is the node currently at the given index. We'll insert the new node in between these two. Note that `prev` can be nil (index is 0), `next` can be nil (index equals size of the list), or both can be nil if the list is empty.

2. Create the new node and connect the `previous` and `next` pointers. Because the local `prev` and `next` variables are optionals and may be nil, so we use optional chaining here.

3. If the new node is being inserted at the front of the list, we need to update the `head` pointer. (Note: If the list had a tail pointer, you'd also need to update that pointer here if `next == nil`, because that means the last element has changed.)

Try it out:

```swift
list.insert("Swift", atIndex: 1)
list[0]     // "Hello"
list[1]     // "Swift"
list[2]     // "World"
```

Also try adding new nodes to the front and back of the list, to verify that this works properly.

> **Note:** The `nodesBeforeAndAfter()` and `insert(atIndex)` functions can also be used with a singly linked list because we don't depend on the node's `previous` pointer to find the previous element.

What else do we need? Removing nodes, of course! First we'll do `removeAll()`, which is really simple:

```swift
  public func removeAll() {
    head = nil
  }
```

If you had a tail pointer, you'd set it to `nil` here too.

Next we'll add some functions that let you remove individual nodes. If you already have a reference to the node, then using `removeNode()` is the most optimal because you don't need to iterate through the list to find the node first. 

```swift
  public func remove(node: Node) -> T {
    let prev = node.previous
    let next = node.next
    
    if let prev = prev {
      prev.next = next
    } else {
      head = next
    }
    next?.previous = prev
    
    node.previous = nil
    node.next = nil
    return node.value
  }
```

When we take this node out of the list, we break the links to the previous node and the next node. To make the list whole again we must connect the previous node to the next node.

Don't forget the `head` pointer! If this was the first node in the list then `head` needs to be updated to point to the next node. (Likewise for when you have a tail pointer and this was the last node). Of course, if there are no more nodes left, `head` should become nil.

Try it out:

```swift
list.remove(list.first!)   // "Hello"
list.count                     // 2
list[0]                        // "Swift"
list[1]                        // "World"
```

If you don't have a reference to the node, you can use `removeLast()` or `removeAt()`:

```swift
  public func removeLast() -> T {
    assert(!isEmpty)
    return remove(node: last!)
  }

  public func removeAt(_ index: Int) -> T {
    let node = nodeAt(index)
    assert(node != nil)
    return remove(node: node!)
  }
```

All these removal functions also return the value from the removed element. 

```swift
list.removeLast()              // "World"
list.count                     // 1
list[0]                        // "Swift"

list.removeAt(0)          // "Swift"
list.count                     // 0
```

> **Note:** For a singly linked list, removing the last node is slightly more complicated. You can't just use `last` to find the end of the list because you also need a reference to the second-to-last node. Instead, use the `nodesBeforeAndAfter()` helper method. If the list has a tail pointer, then `removeLast()` is really quick, but you do need to remember to make `tail` point to the previous node.

There's a few other fun things we can do with our `LinkedList` class. It's handy to have some sort of readable debug output:

```swift
extension LinkedList: CustomStringConvertible {
  public var description: String {
    var s = "["
    var node = head
    while node != nil {
      s += "\(node!.value)"
      node = node!.next
      if node != nil { s += ", " }
    }
    return s + "]"
  }
}
```

This will print the list like so:

	[Hello, Swift, World]

How about reversing a list, so that the head becomes the tail and vice versa? There is a very fast algorithm for that:

```swift
  public func reverse() {
    var node = head
    while let currentNode = node {
      node = currentNode.next
      swap(&currentNode.next, &currentNode.previous)
      head = currentNode
    }
  }
```

This loops through the entire list and simply swaps the `next` and `previous` pointers of each node. It also moves the `head` pointer to the very last element. (If you had a tail pointer you'd also need to update it.) You end up with something like this:

	         +--------+    +--------+    +--------+    +--------+
	tail --->|        |<---|        |<---|        |<---|        |---> nil
	         | node 0 |    | node 1 |    | node 2 |    | node 3 |
	 nil <---|        |--->|        |--->|        |--->|        |<--- head
	         +--------+    +--------+    +--------+    +--------+

Arrays have `map()` and `filter()` functions, and there's no reason why linked lists shouldn't either.

```swift
  public func map<U>(transform: T -> U) -> LinkedList<U> {
    let result = LinkedList<U>()
    var node = head
    while node != nil {
      result.append(transform(node!.value))
      node = node!.next
    }
    return result
  }
```

You can use it like this:

```swift
let list = LinkedList<String>()
list.append("Hello")
list.append("Swifty")
list.append("Universe")

let m = list.map { s in s.characters.count }
m  // [5, 6, 8]
```

And here's filter:

```swift
  public func filter(predicate: T -> Bool) -> LinkedList<T> {
    let result = LinkedList<T>()
    var node = head
    while node != nil {
      if predicate(node!.value) {
        result.append(node!.value)
      }
      node = node!.next
    }
    return result
  }
```

And a silly example:

```swift
let f = list.filter { s in s.characters.count > 5 }
f    // [Universe, Swifty]
```

Exercise for the reader: These implementations of `map()` and `filter()` aren't very fast because they `append()` the new node to the end of the new list. Recall that append is **O(n)** because it needs to scan through the entire list to find the last node. Can you make this faster? (Hint: keep track of the last node that you added.)

## An alternative approach

The version of `LinkedList` you've seen so far uses nodes that are classes and therefore have reference semantics. Nothing wrong with that, but that does make them a bit more heavyweight than Swift's other collections such as `Array` and `Dictionary`.

It is possible to implement a linked list with value semantics using an enum. That would look somewhat like this:

```swift
enum ListNode<T> {
  indirect case node(T, next: ListNode<T>)
  case end
}
```

The big difference with the class-based version is that any modification you make to this list will result in a *new copy* being created. Whether that's what you want or not depends on the application.

[I might fill out this section in more detail if there's a demand for it.]

## Some things to keep in mind

Linked lists are flexible but many operations are **O(n)**.

When performing operations on a linked list, you always need to be careful to update the relevant `next` and `previous` pointers, and possibly also the `head` and `tail` pointers. If you mess this up, your list will no longer be correct and your program will likely crash at some point. Be careful!

When processing lists, you can often use recursion: process the first element and then recursively call the function again on the rest of the list. You’re done when there is no next element. This is why linked lists are the foundation of functional programming languages such as LISP.

*Written for Swift Algorithm Club by Matthijs Hollemans*
