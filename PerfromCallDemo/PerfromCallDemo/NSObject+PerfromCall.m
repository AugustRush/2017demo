//
//  NSObject+PerfromCall.m
//  PerfromCallDemo
//
//  Created by AugustRush on 2017/2/28.
//  Copyright © 2017年 August. All rights reserved.
//


#import "NSObject+PerfromCall.h"

struct RawArguments
{
    void *fptr;
    
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t r8;
    uint64_t r9;
    
    uint64_t stackArgsCount;
    uint64_t *stackArgs;
    
    uint64_t rax_ret;
    uint64_t rdx_ret;
    
    uint64_t isStretCall;
};

void performCall(struct RawArguments *);
int performAdd(int a, int b);

@implementation NSObject (PerfromCall)

- (void)callTest {
    struct RawArguments *arguments = malloc(sizeof(struct RawArguments));
    memcpy(&arguments->rdi, (void*)&self, 8);
    SEL sel = @selector(method1:);
    NSUInteger size;
    NSGetSizeAndAlignment(":", &size, NULL);
    memcpy(&arguments->rsi, &sel, size);
    arguments->fptr = [self methodForSelector:sel];
    
    int a = 20;
    memcpy(&arguments->rdx, &a, sizeof(int));
    
    performCall(arguments);
    
    NSUInteger rsize;
    NSGetSizeAndAlignment("@", &rsize, NULL);
    void *rv = alloca(rsize);
    memcpy(&rv, &arguments->rax_ret, rsize);
    
    NSLog(@"arguments rax is %llu rdx is %llu value is %@",arguments->rax_ret,arguments->rdx_ret,(__bridge NSArray *)rv);
//    free(rv);
    free(arguments);
}

- (NSArray *)method1:(int)a {
    NSLog(@"call method1 %d",a);
    return @[@(15 + a),@100];
}

@end
