//
//  BICollectionViewStackLayout.m
//  CustomCollectionViewLayout
//
//  Created by AugustRush on 2017/8/14.
//  Copyright © 2017年 August. All rights reserved.
//

#import "BICollectionViewStackLayout.h"

@interface _BICollectionViewStackLayoutLineAttributes : NSObject

@property (nonatomic, readonly) CGFloat maxLineHeight;

- (void)addAttributes:(UICollectionViewLayoutAttributes *)attr;
- (void)adjustAttributesOringinXWithCurPage:(NSUInteger)curPage width:(CGFloat)pageWidth leftMargin:(CGFloat)left rightMargin:(CGFloat)right itemsTotalWidth:(CGFloat)itemsTotalWidth;
- (void)setOriginY:(CGFloat)y;

@end

@implementation _BICollectionViewStackLayoutLineAttributes {
    NSMutableArray<UICollectionViewLayoutAttributes *> *_attributes;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _attributes = [NSMutableArray array];
    }
    return self;
}

- (void)addAttributes:(UICollectionViewLayoutAttributes *)attr {
    [_attributes addObject:attr];
    _maxLineHeight = MAX(attr.size.height, _maxLineHeight);
}

- (void)adjustAttributesOringinXWithCurPage:(NSUInteger)curPage width:(CGFloat)pageWidth leftMargin:(CGFloat)left rightMargin:(CGFloat)right itemsTotalWidth:(CGFloat)itemsTotalWidth {
    CGFloat remainW = pageWidth - left - right;
    CGFloat spacing = (remainW - itemsTotalWidth) / (_attributes.count - 1);
    CGFloat prevAttrMaxX = pageWidth * curPage + left;
    for (NSUInteger index = 0; index < _attributes.count; index++) {
        UICollectionViewLayoutAttributes *attr = _attributes[index];
        attr.frame = CGRectMake(prevAttrMaxX, 0, attr.size.width, attr.size.height);
        prevAttrMaxX = CGRectGetMaxX(attr.frame) + spacing;
    }
}

- (void)setOriginY:(CGFloat)y {
    for (UICollectionViewLayoutAttributes *attr in _attributes) {
        CGRect frame = attr.frame;
        frame.origin.y = y;
        attr.frame = frame;
    }
}

@end

@interface _BICollectionViewStackLayoutPageAttributes : NSObject

@property (nonatomic, assign) NSUInteger lines;
@property (nonatomic, assign) BOOL calculated;

- (void)addLineAttributes:(_BICollectionViewStackLayoutLineAttributes *)line;
- (void)adjustAttributesOriginYWithPageHeight:(CGFloat)pageHeight topMargin:(CGFloat)topMargin bottomMargin:(CGFloat)bottomMargin linesTotalHeight:(CGFloat)linesTotalHeight;

@end

@implementation _BICollectionViewStackLayoutPageAttributes {
    NSMutableArray *_lineAttributesArray;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _lineAttributesArray = [NSMutableArray array];
    }
    return self;
}

- (void)addLineAttributes:(_BICollectionViewStackLayoutLineAttributes *)line {
    [_lineAttributesArray addObject:line];
}

- (void)adjustAttributesOriginYWithPageHeight:(CGFloat)pageHeight topMargin:(CGFloat)topMargin bottomMargin:(CGFloat)bottomMargin linesTotalHeight:(CGFloat)linesTotalHeight {
    linesTotalHeight = (linesTotalHeight / _lineAttributesArray.count) * _lines;
    CGFloat remainH = pageHeight - linesTotalHeight - topMargin - bottomMargin;
    CGFloat vSpacing = remainH / (_lines - 1);
    CGFloat prevLineY = 0.0;
    for (NSUInteger index = 0 ; index < _lineAttributesArray.count; index++) {
        _BICollectionViewStackLayoutLineAttributes *lineAttr = _lineAttributesArray[index];
        [lineAttr setOriginY:prevLineY];
        prevLineY += (lineAttr.maxLineHeight + vSpacing);
    }
}

@end

@implementation BICollectionViewStackLayout {
    NSMapTable<NSIndexPath *,UICollectionViewLayoutAttributes *> *_layoutAttributes;
    NSMutableArray<_BICollectionViewStackLayoutPageAttributes *> *_pageAttributesArray;
    CGSize _contentSize;
}

#pragma mark - life cycle methods

- (instancetype)init {
    self = [super init];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        [self commonInit];
    }
    return self;
}

#pragma mark - private methods

- (void)commonInit {
    _numberOfLinesPerPage = 3;
    _itemMinimalHorizontalSpacing = 1.0;
    _contentInsets = UIEdgeInsetsMake(5, 5, 5, 5);
    _layoutAttributes = [NSMapTable strongToWeakObjectsMapTable];
    _pageAttributesArray = [NSMutableArray array];
}

- (_BICollectionViewStackLayoutLineAttributes *)makeNewLineAttributes {
    return [_BICollectionViewStackLayoutLineAttributes new];
}

- (_BICollectionViewStackLayoutPageAttributes *)makeNewPageAttributes {
    _BICollectionViewStackLayoutPageAttributes *pageAttributes = [_BICollectionViewStackLayoutPageAttributes new];
    pageAttributes.lines = self.numberOfLinesPerPage;
    return pageAttributes;
}

#pragma mark - custom UICollectionViewLayout methods

- (void)prepareLayout {
    [super prepareLayout];
    //clean up
    [_layoutAttributes removeAllObjects];
    _contentSize = CGSizeZero;
    //caculate attibutes
    CGFloat collectionViewWidth = CGRectGetWidth(self.collectionView.bounds);
    CGFloat collectionViewHeight = CGRectGetHeight(self.collectionView.bounds);
    
    NSAssert([self.collectionView numberOfSections] == 1, @"number of sections should equal to 1.");
    CGFloat hs = collectionViewWidth - _contentInsets.left - _contentInsets.right;
    // for calculate
    CGFloat calaulte_hs = hs;
    CGFloat itemsTotalWidthEveryLine = 0.0;
    CGFloat linesTotalHeightEveryPage = 0.0;
    NSUInteger indexForLine = 0;
    NSUInteger currentLine = 0;
    NSUInteger currentPage = 0;
    //
    _BICollectionViewStackLayoutLineAttributes *lineAttributes = [self makeNewLineAttributes];
    _BICollectionViewStackLayoutPageAttributes *pageAttributes = [self makeNewPageAttributes];
    
    NSUInteger numberOfRows = [self.collectionView numberOfItemsInSection:0];
    id delegate = self.collectionView.delegate;
    for (NSUInteger row = 0; row < numberOfRows; row++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:row inSection:0];
        CGSize itemSize = [delegate stackLayout:self sizeForItemAtIndexPath:indexPath];
        //
        UICollectionViewLayoutAttributes *attr = [UICollectionViewLayoutAttributes layoutAttributesForCellWithIndexPath:indexPath];
        attr.size = itemSize;
        //
        BOOL isNewLine = (calaulte_hs - itemSize.width - _itemMinimalHorizontalSpacing * indexForLine < -1);
        BOOL isLastItem = (row == numberOfRows - 1);
        if (isNewLine) {
            [pageAttributes addLineAttributes:lineAttributes];
            // adjust attributes in line
            [lineAttributes adjustAttributesOringinXWithCurPage:currentPage width:collectionViewWidth leftMargin:_contentInsets.left rightMargin:_contentInsets.right itemsTotalWidth:itemsTotalWidthEveryLine];
            //
            linesTotalHeightEveryPage += lineAttributes.maxLineHeight;
            // new line
            itemsTotalWidthEveryLine = itemSize.width;
            lineAttributes = [self makeNewLineAttributes];
            calaulte_hs = hs - itemSize.width;
            indexForLine = 1;
            currentLine++;
            if (currentLine % _numberOfLinesPerPage == 0 || isLastItem) {
                //
                [_pageAttributesArray addObject:pageAttributes];
                //
                [pageAttributes adjustAttributesOriginYWithPageHeight:collectionViewHeight topMargin:_contentInsets.top bottomMargin:_contentInsets.bottom linesTotalHeight:linesTotalHeightEveryPage];
                //new page
                pageAttributes = [self makeNewPageAttributes];
                //reset line total height
                linesTotalHeightEveryPage = 0.0;
                currentPage++;
            }
        } else {
            calaulte_hs -= itemSize.width;
            itemsTotalWidthEveryLine += itemSize.width;
            indexForLine++;
        }
        //add record
        [lineAttributes addAttributes:attr];
        // for last item
        if (isLastItem) {
            if (!isNewLine) {
                [lineAttributes adjustAttributesOringinXWithCurPage:currentPage width:collectionViewWidth leftMargin:_contentInsets.left rightMargin:_contentInsets.right itemsTotalWidth:itemsTotalWidthEveryLine];
                [pageAttributes addLineAttributes:lineAttributes];
                linesTotalHeightEveryPage += lineAttributes.maxLineHeight;
            }
            [_pageAttributesArray addObject:pageAttributes];
            //
            [pageAttributes adjustAttributesOriginYWithPageHeight:collectionViewHeight topMargin:_contentInsets.top bottomMargin:_contentInsets.bottom linesTotalHeight:linesTotalHeightEveryPage];
        }
        //add to map for find
        [_layoutAttributes setObject:attr forKey:indexPath];
    }
    
    // content size
    _contentSize = CGSizeMake(collectionViewWidth * (currentPage + 1), collectionViewHeight);
}

- (CGSize)collectionViewContentSize {
    return _contentSize;
}

- (NSArray<UICollectionViewLayoutAttributes *> *)layoutAttributesForElementsInRect:(CGRect)rect {
    NSMutableArray *array = [NSMutableArray array];
    for (UICollectionViewLayoutAttributes *attr in _layoutAttributes.objectEnumerator) {
        if (CGRectIntersectsRect(rect, attr.frame)) {
            [array addObject:attr];
        }
    }
    return [array copy];
}

- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewLayoutAttributes *attr = [_layoutAttributes objectForKey:indexPath];
    return attr;
}

@end
