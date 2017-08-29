//
//  BIEmojiCollectionViewLayout.m
//  CustomCollectionViewLayout
//
//  Created by AugustRush on 2017/8/10.
//  Copyright © 2017年 August. All rights reserved.
//

#import "BICollectionViewFixedSizeLayout.h"

@implementation BICollectionViewFixedSizeLayout {
    NSMutableDictionary<NSIndexPath *,UICollectionViewLayoutAttributes *> *_layoutAttributes;
    CGSize _contentSize;
    NSUInteger _numberOfColumnsPerPage;
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

#pragma mark - public methods

- (BOOL)isLastItemPerPageAtIndexPath:(NSIndexPath *)indexPath {
    if (self.anchorLastItemPerPage) {
        if ((indexPath.row + 1) % (_numberOfColumnsPerPage * _numberOfLinesPerPage) == 0 ||
            indexPath.row == [self.collectionView numberOfItemsInSection:0] - 1) {
            return YES;
        }
    }
    return NO;
}

#pragma mark - private methods

- (void)commonInit {
    _itemSize = CGSizeMake(40, 40);
    _numberOfLinesPerPage = 3;
    _anchorLastItemPerPage = NO;
    _minimalColumnSpacing = 1.0;
    _contentInsets = UIEdgeInsetsMake(5, 5, 5, 5);
    _layoutAttributes = [NSMutableDictionary dictionary];
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
    
    CGFloat itemWidth = _itemSize.width;
    CGFloat itemHeight = _itemSize.height;
    _numberOfColumnsPerPage = (collectionViewWidth - _contentInsets.left - _contentInsets.right + _minimalColumnSpacing) / (_itemSize.width + _minimalColumnSpacing);
    
    NSAssert([self.collectionView numberOfSections] == 1, @"number of sections should equal to 1.");
    NSUInteger numberOfItemsPerPage = _numberOfColumnsPerPage * _numberOfLinesPerPage;
    CGFloat columnSpacing = (collectionViewWidth - _contentInsets.left - _contentInsets.right - _numberOfColumnsPerPage * itemWidth) / (_numberOfColumnsPerPage - 1);
    CGFloat lineSpacing = (collectionViewHeight - _contentInsets.top - _contentInsets.bottom - _numberOfLinesPerPage * itemHeight) / (_numberOfLinesPerPage - 1);
    NSUInteger numberOfRows = [self.collectionView numberOfItemsInSection:0];
    for (NSUInteger row = 0; row < numberOfRows; row++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:row inSection:0];
        NSUInteger currentPage = floor(row / numberOfItemsPerPage);
        NSUInteger currentItemOnPageIndex = (row % numberOfItemsPerPage);
        //
        CGFloat originX = 0.0;
        CGFloat originY = 0.0;
        if (_anchorLastItemPerPage && (row == numberOfRows - 1)) {
            originX = (currentPage + 1) * collectionViewWidth - _contentInsets.right - itemWidth;
            originY = collectionViewHeight - _contentInsets.bottom - itemHeight;
        } else {
            originX = _contentInsets.left + (row % _numberOfColumnsPerPage) * (columnSpacing + itemWidth) + currentPage * collectionViewWidth;
            originY = _contentInsets.top + (currentItemOnPageIndex / _numberOfColumnsPerPage) * (lineSpacing + itemHeight);
        }
        
        // all attributes
        UICollectionViewLayoutAttributes *attributes = [UICollectionViewLayoutAttributes layoutAttributesForCellWithIndexPath:indexPath];
        attributes.size = CGSizeMake(itemWidth, itemHeight);
        attributes.frame = CGRectMake(originX, originY, itemWidth, itemHeight);
        _layoutAttributes[indexPath] = attributes;
    }
    
    // content size
    NSUInteger pages = ceil(numberOfRows / (1.0 * numberOfItemsPerPage));
    _contentSize = CGSizeMake(collectionViewWidth * pages, collectionViewHeight);
}

- (CGSize)collectionViewContentSize {
    return _contentSize;
}

- (NSArray<UICollectionViewLayoutAttributes *> *)layoutAttributesForElementsInRect:(CGRect)rect {
    NSArray *attributes = [_layoutAttributes.allValues filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL(UICollectionViewLayoutAttributes *  _Nullable evaluatedObject, NSDictionary<NSString *,id> * _Nullable bindings) {
        if (CGRectIntersectsRect(rect, evaluatedObject.frame)) {
            return YES;
        }
        return NO;
    }]];
    return attributes;
}

- (UICollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath {
    return _layoutAttributes[indexPath];
}

@end
