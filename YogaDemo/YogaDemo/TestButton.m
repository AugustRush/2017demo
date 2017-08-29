//
//  TestButton.m
//  YogaDemo
//
//  Created by AugustRush on 2017/4/8.
//  Copyright © 2017年 August. All rights reserved.
//

#import "TestButton.h"

@implementation TestButton

- (CGSize)sizeThatFits:(CGSize)size {
    CGSize fsize = [super sizeThatFits:size];
    NSLog(@"fit size is %@",NSStringFromCGSize(size));
    return CGSizeMake(NAN, NAN);
}

@end
