
load("UIView")

class Person extends UIView {
	init(){
		self = super.init();
		if (self) {
			self.backgroundColor = UIColor.redColor();
		}
		return self;
	}
}