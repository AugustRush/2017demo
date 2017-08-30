// 'use strict';

// Example 1: Creating a new class (declaration-form)
// ===============================================================

// A base class is defined using the new reserved 'class' keyword
export class Polygon {
  // ..and an (optional) custom class constructor. If one is
  // not supplied, a default constructor is used instead:
  // constructor() { }
  constructor(height, width) {
    this.name = 'Polygon';
    this.height = height;
    this.width = width;
  }

  // Simple class instance methods using short-hand method
  // declaration
  sayName() {
  	print(this.name)
  }

  sayHistory() {
  	print('sayHistory ....')
  }
}

// Classes are used just like ES5 constructor functions:
let p = new Polygon(300, 400);
p.sayName();

// Example 2: Creating a new class (expression-form)
// ===============================================================

// Our Polygon class above is an example of a Class declaration.
// ES6 classes also support Class expressions - just another way
// of defining a new class. For example:
const MyPoly = class Poly {
  getPolyName() {
  	print(this.height)
  }
};

let inst = new MyPoly();
inst.getPolyName();

// Example 3: Extending an existing class
// ===============================================================

// Classes support extending other classes, but can also extend
// other objects. Whatever you extend must be a constructor.
//
// Let's extend the Polygon class to create a new derived class
// called Square.
class Square extends Polygon {
  constructor(length) {
    // The reserved 'super' keyword is for making super-constructor
    // calls and allows access to parent methods.
    //
    // Here, it will call the parent class' constructor with lengths
    // provided for the Polygon's width and height
    super(length, length);
    // Note: In derived classes, super() must be called before you
    // can use 'this'. Leaving this out will cause a reference error.
    this.name = 'Square';
  }

  // Getter/setter methods are supported in classes,
  // similar to their ES5 equivalents
  get area() {
    return this.height * this.width;
  }

  set area(value) {
    this.area = value;
  }
}

let s = new Square(5);

s.sayName();

// Example 4: Subclassing methods of a parent class
// ===============================================================

class Rectangle extends Polygon {
  constructor(height, width) {
    super(height, width);
    this.name = 'Rectangle';
  }
  // Here, sayName() is a subclassed method which
  // overrides their superclass method of the same name.
  sayName() {
    super.sayHistory();
  }
}

let r = new Rectangle(50, 60);
r.sayName();

// Example 5: Defining static methods
// ===============================================================

// Classes support static members which can be accessed without an
// instance being present.
class Triple {
  // Using the 'static' keyword creates a method which is associated
  // with a class, but not with an instance of the class.
  static triple(n) {
    n = n || 1;
    return n * 3;
  }
}

// super.prop in this example is used for accessing super-properties from
// a parent class. This works fine in static methods too:
class BiggerTriple extends Triple {
  static triple(n) {
    return super.triple(n) * super.triple(n);
  }
}
// var tp = new Triple();
// ChromeSamples.log(tp.triple()); tp.triple is not a function

// Example 6: Subclassing built-in classes and DOM
// ===============================================================

// Extend Date built-in
class MyDate extends Date {
  constructor() {
    super();
  }

  getFormattedDate() {
    var months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep',
      'Oct', 'Nov', 'Dec'];
    return this.getDate() + '-' + months[this.getMonth()] + '-' +
      this.getFullYear();
  }
}

var aDate = new MyDate();
// Extend Uint8Array
class ExtendedUint8Array extends Uint8Array {
  constructor() {
    super(10);
    this[0] = 255;
    this[1] = 0xFFA;
  }
}

// var eua = new ExtendedUint8Array();

// // Extend DOM Audio element
// class MyAudio extends Audio {
//   constructor() {
//     super();
//     this._lyrics = '';
//   }

//   get lyrics() {
//     return this._lyrics;
//   }

//   set lyrics(str) {
//     this._lyrics = str;
//   }
// }

// var player = new MyAudio();
// player.controls = true;
// player.lyrics = 'Never gonna give you up';
// document.querySelector('body').appendChild(player);

// Note: The V8 in Chrome 42 supports subclassing built-ins but Arrays.
// Subclassing arrays supported in Chrome 43.

class Stack extends Array {
  constructor() {
    super();
  }

  top() {
    return this[this.length - 1];
  }
}

// const Component = class AUComponent {
// 	render() {
// 		print("this is render function");
// 		return undefined
// 	}
// };

class Cell extends Component {
	render() {
		return `
    		<View style={styles.container}>
      			<Text style={styles.container_title}>Hello World</Text>
    		</View>
  		);
      `
	}
}

// var cell = new Cell();
// print(cell.render());


