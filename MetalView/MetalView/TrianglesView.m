//
//  TrianglesView.m
//  MetalView
//
//  Created by AugustRush on 2017/3/2.
//  Copyright © 2017年 August. All rights reserved.
//

#import "TrianglesView.h"
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

@interface TrianglesView ()

@property (nonatomic, strong) CAMetalLayer *metalLayer;
@property (nonatomic, strong) id<MTLDevice> device;
@property (nonatomic, strong) id<MTLBuffer> positionBuffer;
@property (nonatomic, strong) id<MTLBuffer> colorBuffer;
@property (nonatomic, strong) id<MTLRenderPipelineState> pipeline;

@end

@implementation TrianglesView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self buildDevice];
        [self buildVertexBuffers];
        [self buildPipeline];
    }
    return self;
}

+ (Class)layerClass {
    return [CAMetalLayer class];
}

- (void)buildVertexBuffers {
    static const float positions[] =
    {
        0.0,  0.5, 0, 1,
        -0.5, -0.5, 0, 1,
        0.5, -0.5, 0, 1,
    };
    
    static const float colors[] =
    {
        1, 0, 0, 1,
        0, 1, 0, 1,
        0, 0, 1, 1,
    };

    self.positionBuffer = [self.device newBufferWithBytes:positions length:sizeof(positions) options:MTLResourceOptionCPUCacheModeDefault];
    self.colorBuffer = [self.device newBufferWithBytes:colors length:sizeof(colors) options:MTLResourceOptionCPUCacheModeDefault];
}

- (void)buildPipeline {
    
    id<MTLLibrary> library = [self.device newDefaultLibrary];
    
    id<MTLFunction> vertexFunc = [library newFunctionWithName:@"vertex_main"];
    id<MTLFunction> fragmentFunc = [library newFunctionWithName:@"fragment_main"];
    
    MTLRenderPipelineDescriptor *pipelineDescriptor = [MTLRenderPipelineDescriptor new];
    pipelineDescriptor.vertexFunction = vertexFunc;
    pipelineDescriptor.fragmentFunction = fragmentFunc;
    pipelineDescriptor.colorAttachments[0].pixelFormat = self.metalLayer.pixelFormat;
    
    self.pipeline = [self.device newRenderPipelineStateWithDescriptor:pipelineDescriptor
                                                                error:NULL];
}

- (void)redraw {
    //
    id<CAMetalDrawable> drawable = [self.metalLayer nextDrawable];
    id<MTLTexture> framebufferTexture = drawable.texture;
    
    MTLRenderPassDescriptor *renderPass = [MTLRenderPassDescriptor renderPassDescriptor];
    renderPass.colorAttachments[0].texture = framebufferTexture;
    renderPass.colorAttachments[0].clearColor = MTLClearColorMake(0.5, 0.5, 0.5, 1);
    renderPass.colorAttachments[0].storeAction = MTLStoreActionStore;
    renderPass.colorAttachments[0].loadAction = MTLLoadActionClear;
    
    //
    id<MTLCommandQueue> commandQueue = [self.device newCommandQueue];
    id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    
    id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPass];
    [commandEncoder setRenderPipelineState:self.pipeline];
    [commandEncoder setVertexBuffer:self.positionBuffer offset:0 atIndex:0 ];
    [commandEncoder setVertexBuffer:self.colorBuffer offset:0 atIndex:1 ];
    [commandEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3 instanceCount:1];
    [commandEncoder endEncoding];
    
    [commandBuffer presentDrawable:drawable];
    [commandBuffer commit];
}

- (void)buildDevice {
    _device = MTLCreateSystemDefaultDevice();
    _metalLayer = (CAMetalLayer *)self.layer;
    _metalLayer.device = _device;
    _metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
}

- (void)didMoveToWindow {
    [super didMoveToWindow];
    [self redraw];
}


@end
