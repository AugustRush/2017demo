{
	let a = 123;
	var b = '456';
}

// print(a);// will throw a error , beacausse it's let decleared
print(b + ' is ' + typeof(b));
{
  let [o,t,h] = [1,2,3]
  print(o + t + h)
  //解构成功
  let [head, ...tail] = [1,2,3,4]
  print(head + '---' + tail)
//部分结构
  let [x,y] = [1,2,3]
  let [c,[d,e],f] = [1,[2],3];
  print('x is ',x,' y is ',y);
  print('c is ',c,' d is ',d, 'f is ',f);
}


//字符串
{
	let a = '\u3455'
	print(a)
	let b = '\u{20bb8}'
	print(b)
	print('wer'.charAt(0),' ', '你好'.charAt(0));
	let c = 'august rush';
	if (c.includes('a')) {
		c = c.repeat(3)
	}
	print(c);
	//补全
	let x = 'x'.padStart(5,'mnb');//不够长度5，用‘mnb’补全
	var y = 'y'.padEnd(10,'cvx');
	print(x, ' ', y);

	function fy() {
		return y;
	}

	//模版字符串(可以嵌入变量和函数)
	let list = `
		<ul>
  			<li class = ${x}>first</li>
  			<li type = ${fy()}>second</li>
		</ul>
	`;
	print(list)
	//模版编译
	var template = `
		<ul>
  			<% for(var i=0; i < data.supplies.length; i++) { %>
   			 <li><%= data.supplies[i] %></li>
  			<% } %>
		</ul>`;

		function compile(template){
  var evalExpr = /<%=(.+?)%>/g;
  var expr = /<%([\s\S]+?)%>/g;

  template = template
    .replace(evalExpr, '`); \n  echo( $1 ); \n  echo(`')
    .replace(expr, '`); \n $1 \n  echo(`');

  template = 'echo(`' + template + '`);';
	print('echo template is ',template)

  var script =
  `(function parse(data){
    var output = "";

    function echo(html){
      output += html;
    }

    ${ template }

    return output;
  })`;

  return script;
}

var parse = eval(compile(template));
var div = parse({ supplies: [ "broom", "mop", "cleaner" ] });

print('parse is ',parse);
print('div is ',div);
}

//Number

{
	let a = 0b011100011;//二进制
	let b = 0o1247512413;//八进制
	let c = 0x6712391828ff;
	print(a);
	print(b);
	print(c);
}

//Array
{
	let arrayLike = {
		'0' : 'a',
		'1' : 'b',
		length : 3
	};
	var arr1 = [].slice.call(arrayLike);//ES5
	var arr2 = Array.from(arrayLike);//ES6
	print(arr1);
	print(arr2);
	let a = Array.from('some');
	print('some to array is ',a);

	a.forEach(function(p){
		if (p === 'o') {
			print(a.indexOf(p));
		}
	});

	let b = [1,,2,,3,,4];
	b = Array.from(b, (p) => (p || 0) + 16);
	print('ssssss ',b);

	let c = Array.of(1,2,4);
	print(c);

	let d = new Array(10).fill(5);
	print('d is ',d);
	d = d.fill(0,1,5);
	print('re fill d is ',d);

	//遍历
	for(let [index, e] of d.entries()) {
		print(index,e);
	}
}

//function



