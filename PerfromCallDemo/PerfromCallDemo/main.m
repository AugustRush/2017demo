//
//  main.m
//  PerfromCallDemo
//
//  Created by AugustRush on 2017/2/28.
//  Copyright © 2017年 August. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSObject+PerfromCall.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSObject *test = [[NSObject alloc] init];
        [test callTest];
    }
    return 0;
}
