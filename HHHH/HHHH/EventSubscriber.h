//
//  EventSubscriber.h
//  HHHH
//
//  Created by AugustRush on 2017/7/20.
//  Copyright © 2017年 August. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EventSubscriber : NSObject

@property (nonatomic, weak) id observer;
@property (nonatomic, copy) id callback;

@end
