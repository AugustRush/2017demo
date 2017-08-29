//
//  RVAnimation_Private.h
//  Revolved
//
//  Created by Bartosz Ciechanowski on 25.08.2013.
//  Copyright (c) 2013 Bartosz Ciechanowski. All rights reserved.
//

#import "RVAnimation.h"

@class RVSprite;
@interface RVAnimation ()

@property (nonatomic, strong) NSString *key;
@property (nonatomic, weak) id target;

@end
