//
//  RVMeshController.h
//  Revolved
//
//  Created by Bartosz Ciechanowski on 10.08.2013.
//  Copyright (c) 2013 Bartosz Ciechanowski. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RVMeshController : NSObject

@property (nonatomic, readonly) GLuint VAO;
@property (nonatomic, readonly) GLuint indiciesCount;

- (void)setupOpenGL;

@end
