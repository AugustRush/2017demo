//
//  TextView.m
//  TextKitDemo
//
//  Created by AugustRush on 2017/4/4.
//  Copyright © 2017年 August. All rights reserved.
//

#import "TextView.h"

@implementation TextView

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self commonInit];
    }
    return self;
}


- (void)commonInit {
    self.layoutManager = [[NSLayoutManager alloc] init];
    
    self.textStorage = [[NSTextStorage alloc] initWithString:@"This class demonstrates a technique for creating a view that lets rich text flow across multiple columns in just a few lines of code. But we’re really just scratching the surface here. Besides flowing across multiple rectangles, Text Kit will let you do plenty of other things, including drawing text inside the path of an arbitrary shape, making text flow around other paths, and more. You can learn more about thse techniques by looking at Apple’s iOS Text Kit Overview, as well as their Mac documentation for the Cocoa text system, which is where much of Text Kit’s functionality originated."];
    
    [self createColumns];

}

- (void)setTextStorage:(NSTextStorage *)textStorage {
    _textStorage = [[NSTextStorage alloc] initWithAttributedString:textStorage];
    [self.textStorage addLayoutManager:self.layoutManager];
    [self setNeedsDisplay];
}

- (void)createColumns {
    // Remove any existing text containers, since we will recreate them.
    for (NSUInteger i = [self.layoutManager.textContainers count]; i > 0;) {
        [self.layoutManager removeTextContainerAtIndex:--i];
    }
    
    // Capture some frequently-used geometry values in local variables.
    CGRect bounds = self.bounds;
    CGFloat x = bounds.origin.x;
    CGFloat y = bounds.origin.y;
    
    // These are effectively constants. If you want to make this class more
    // extensible, turning these into public properties would be a nice start!
    NSUInteger columnCount = 2;
    CGFloat interColumnMargin = 10;
    
    // Calculate sizes for building a series of text containers.
    CGFloat totalMargin = interColumnMargin * (columnCount - 1);
    CGFloat columnWidth = (bounds.size.width - totalMargin) / columnCount;
    CGSize columnSize = CGSizeMake(columnWidth, bounds.size.height);
    
    NSMutableArray *containers = [NSMutableArray arrayWithCapacity:columnCount];
    NSMutableArray *origins = [NSMutableArray arrayWithCapacity:columnCount];
    
    for (NSUInteger i = 0; i < columnCount; i++) {
        // Create a new container of the appropriate size, and add it to our array.
        NSTextContainer *container = [[NSTextContainer alloc] initWithSize:columnSize];
        [containers addObject:container];
        
        // Create a new origin point for the container we just added.
        NSValue *originValue = [NSValue valueWithCGPoint:CGPointMake(x, y)];
        [origins addObject:originValue];
        
        [self.layoutManager addTextContainer:container];
        x += columnWidth + interColumnMargin;
    }
    self.textOrigins = origins;
}

- (void)drawRect:(CGRect)rect {
    for (NSUInteger i = 0; i < [self.layoutManager.textContainers count]; i++) {
        NSTextContainer *container = self.layoutManager.textContainers[i];
        CGPoint origin = [self.textOrigins[i] CGPointValue];
        
        NSRange glyphRange = [self.layoutManager glyphRangeForTextContainer:container];
        
        [self.layoutManager drawGlyphsForGlyphRange:glyphRange atPoint:origin];
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];
    [self createColumns];
    [self setNeedsDisplay];
}

@end
