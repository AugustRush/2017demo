{
	var a = {a: 2}
	print(a)
	var b = new Object(a);
	print(b);
	var c = new Object(123);
	print(c instanceof Number);
	print('c\' keys is ',Object.keys(c));

	var d = new Object({
		a : 'a',
		b : '123'
	});
	print('d all keys is ',Object.keys(d));
}