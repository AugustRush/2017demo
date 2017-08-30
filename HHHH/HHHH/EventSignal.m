//
//  EventSignal.m
//  HHHH
//
//  Created by AugustRush on 2017/7/20.
//  Copyright © 2017年 August. All rights reserved.
//

#import "EventSignal.h"
#import "EventSubscriber.h"
#import <objc/runtime.h>
#import <UIKit/UIKit.h>

@interface EventSignal ()

@property (nonatomic, strong) NSMutableArray *subscribers;
@property (nonatomic, copy) id fire;

@end

@implementation EventSignal

- (instancetype)initWithProtocol:(Protocol *)protocol {
    self = [super init];
    if (self) {
        _subscribers = [NSMutableArray array];
        __weak typeof(self) weakSelf = self;
        if (protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount0))) {
            _fire = ^{
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire];
            };
        } else if(protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount1))) {
            _fire = ^(void * first) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire1:first];
            };
        } else if(protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount2))) {
            _fire = ^(void * first, void * second) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire2:first :second];
            };
        } else if(protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount3))) {
            _fire = ^(void * first, void * second, void * third) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire3:first :second :third];
            };
        } else if(protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount4))) {
            _fire = ^(void * first, void * second, void * third, void * fourth) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire4:first :second :third :fourth];
            };
        } else if(protocol_conformsToProtocol(protocol, @protocol(BISignalArgsCount5))) {
            _fire = ^(void * first, void * second, void * third, void * fourth, void * fifth) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                [strongSelf internalFire5:first :second :third :fourth :fifth];
            };
        }
    }
    return self;
}

#pragma mark - public methods

- (void)addObserver:(id)observer callback:(id)callback {
    EventSubscriber *sub = [EventSubscriber new];
    sub.observer = observer;
    sub.callback = callback;
    [_subscribers addObject:sub];
}

#pragma mark - private methods

- (void)internalFire {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self))subscriber.callback)(subscriber.observer);
    }
}

- (void)internalFire1:(void * )first {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self, void * ))subscriber.callback)(subscriber.observer, first);
    }
}

- (void)internalFire2:(void * )first :(void * )second {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self, void * , void * ))subscriber.callback)(subscriber.observer, first, second);
    }
}

- (void)internalFire3:(void * )first :(void * )second :(void * )third {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self, void * , void * , void * ))subscriber.callback)(subscriber.observer, first, second, third);
    }
}

- (void)internalFire4:(void * )first :(void * )second :(void * )third :(void * )fourth {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self, void * , void * , void * , void * ))subscriber.callback)(subscriber.observer, first, second, third, fourth);
    }
}

- (void)internalFire5:(void * )first :(void * )second :(void * )third :(void * )fourth :(void * )fifth {
    for (EventSubscriber *subscriber in _subscribers) {
        ((void(^)(id self, void * , void * , void * , void * , void * ))subscriber.callback)(subscriber.observer, first, second, third, fourth,fifth);
    }
}


@end
