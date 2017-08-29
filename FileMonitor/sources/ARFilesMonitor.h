//
//  ARFilesMonitor.h
//  FileMonitor
//
//  Created by AugustRush on 2017/3/19.
//  Copyright © 2017年 August. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ARFilesMonitor : NSObject

- (instancetype)initWithDirectoryPath:(NSString *)path;

- (void)startMonitor;

@end
