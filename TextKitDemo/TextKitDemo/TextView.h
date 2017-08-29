//
//  TextView.h
//  TextKitDemo
//
//  Created by AugustRush on 2017/4/4.
//  Copyright © 2017年 August. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TextView : UIView

@property (copy, nonatomic) NSTextStorage *textStorage;
@property (strong, nonatomic) NSArray *textOrigins;
@property (strong, nonatomic) NSLayoutManager *layoutManager;

@end
