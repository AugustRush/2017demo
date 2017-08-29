//
//  ViewController.m
//  YogaDemo
//
//  Created by AugustRush on 2017/3/12.
//  Copyright © 2017年 August. All rights reserved.
//

#import "ViewController.h"
#import "UIView+Yoga.h"
#import "TestButton.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.view.backgroundColor = [UIColor redColor];

    for (NSUInteger i = 0; i < 4; i++) {
        TestButton *button = [TestButton buttonWithType:UIButtonTypeCustom];
        [button setTitle:@(i).stringValue forState:UIControlStateNormal];
        [button setBackgroundColor:[UIColor greenColor]];
        [self.view addSubview:button];
        
        button.yoga.isEnabled = YES;
        button.yoga.margin = 1;
        if (i == 0) {
            button.yoga.height = 100;
            button.yoga.width = 100;
            button.yoga.alignSelf = YGAlignFlexStart;
        }else {
                button.yoga.flexGrow = 1;
        }
    }
    
    [self.view configureLayoutWithBlock:^(YGLayout * _Nonnull layout) {
        layout.isEnabled = YES;
        layout.flexDirection = YGFlexDirectionRow;
        layout.justifyContent = YGJustifyFlexStart;
        layout.alignItems = YGAlignStretch;
    }];
    
    [self.view.yoga applyLayoutWithSize:CGSizeMake(320, 400) preserveOrigin:YES];
    
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view.yoga applyLayoutWithSize:CGSizeMake(320, 400) preserveOrigin:YES];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
