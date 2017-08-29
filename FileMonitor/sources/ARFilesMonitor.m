//
//  ARFilesMonitor.m
//  FileMonitor
//
//  Created by AugustRush on 2017/3/19.
//  Copyright © 2017年 August. All rights reserved.
//

#import "ARFilesMonitor.h"

@implementation ARFilesMonitor {
    NSString *_directoryPath;
    dispatch_source_t _source;
}

- (instancetype)initWithDirectoryPath:(NSString *)path {
    self = [super init];
    if (self) {
        _directoryPath = path;
    }
    return self;
}

- (void)startMonitor {
    NSURL *URL = [NSURL fileURLWithPath:_directoryPath];
    int const fd =
    open([[URL path] fileSystemRepresentation], O_EVTONLY);
    if (fd < 0) {
        
        NSLog(@"Unable to open the path = %@", [URL path]);
        return;
    }
    _source =
    dispatch_source_create(DISPATCH_SOURCE_TYPE_VNODE, fd,
                           DISPATCH_VNODE_WRITE | DISPATCH_VNODE_RENAME,
                           DISPATCH_TARGET_QUEUE_DEFAULT);
    dispatch_source_set_event_handler(_source, ^() {
        unsigned long const type = dispatch_source_get_data(_source);
        
        switch (type) {
            case DISPATCH_VNODE_WRITE: {
                NSLog(@"目录内容改变!!!");
                break;
            }
            case DISPATCH_VNODE_RENAME: {
                NSLog(@"目录被重命名!!!");
                break;
            }
                
            default:
                break;
        }
    });
    dispatch_source_set_cancel_handler(_source, ^{ close(fd);
    });
    dispatch_resume(_source);
}

@end
