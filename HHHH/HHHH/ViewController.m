//
//  ViewController.m
//  HHHH
//
//  Created by AugustRush on 2017/7/19.
//  Copyright © 2017年 August. All rights reserved.
//

#import "ViewController.h"
#import "EventSignal.h"

CreateSignal(Test, id first, NSUInteger index)
CreateSignal(Some, NSString *des, CGFloat number, NSArray *value)
CreateSignal(Number, CGFloat f, CGFloat s, float t)
CreateSignal(Double, double f, long long int s, float t, NSUInteger f1, NSInteger fif)
@interface ViewController ()

@property (nonatomic, strong) EventSignal<TestSignal> *testSignal;
@property (nonatomic, strong) EventSignal<SomeSignal> *someSignal;
@property (nonatomic, strong) EventSignal<NumberSignal> *numberSignal;
@property (nonatomic, strong) EventSignal<DoubleSignal> *doubleSignal;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    _testSignal = (EventSignal<TestSignal> *)[[EventSignal alloc] initWithProtocol:@protocol(TestSignal)];
    _someSignal = (EventSignal<SomeSignal> *)[[EventSignal alloc] initWithProtocol:@protocol(SomeSignal)];
    _numberSignal = (EventSignal<NumberSignal> *)[[EventSignal alloc] initWithProtocol:@protocol(NumberSignal)];
    _doubleSignal = [(EventSignal<DoubleSignal> *)[EventSignal alloc] initWithProtocol:@protocol(DoubleSignal)];
    
    [_testSignal addObserver:self callback:^(id self, id first, NSUInteger index) {
        NSLog(@"caller is %@ \n index is %lu",first,(unsigned long)index);
    }];
    
    [_someSignal addObserver:self callback:^(id self, NSString *des, CGFloat number, NSArray *value) {
        NSLog(@"some signal is %@ %@ %lf %@", self, des, number, value);
    }];
    
    [_numberSignal addObserver:self callback:^(id self, CGFloat f, CGFloat s, float t) {
        NSLog(@"number signal %@ is f is %f s is %f t is %f",self,f,s,t);
    }];
    
    [_doubleSignal addObserver:self callback:^(id self, double f, long long s, float t, NSUInteger f1, NSInteger fif) {
        NSLog(@"%f %lld %f %lu %ld",f,s,t,(unsigned long)f1,(long)fif);
    }];
    
    _testSignal.fire(@"Just test",10);
    _someSignal.fire(@"you are welcome",1357.2368, @[@3.1415926,@"second item",self]);
    _numberSignal.fire(1.1,2.2,3.3);
    _doubleSignal.fire(1.00345,123982348234,3.1401,2,10);


}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
