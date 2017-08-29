//
//  BICollectionViewStackLayout.h
//  CustomCollectionViewLayout
//
//  Created by AugustRush on 2017/8/14.
//  Copyright © 2017年 August. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BICollectionViewStackLayout;
@protocol BICollectionViewStackLayoutDelegate <NSObject>

@required
- (CGSize)stackLayout:(BICollectionViewStackLayout *)stackLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath;

@end

@interface BICollectionViewStackLayout : UICollectionViewLayout

@property (nonatomic) UIEdgeInsets contentInsets;
@property (nonatomic) NSUInteger numberOfLinesPerPage;
@property (nonatomic) CGFloat itemMinimalHorizontalSpacing;

@end
