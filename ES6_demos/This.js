function des() {
	return 'August ' + this.name;
}

var person = {
	name: 'zjamhsan',
	describe: des
}

print(person.describe())