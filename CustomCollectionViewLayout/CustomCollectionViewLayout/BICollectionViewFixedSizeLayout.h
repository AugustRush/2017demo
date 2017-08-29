//
//  BIEmojiCollectionViewLayout.h
//  CustomCollectionViewLayout
//
//  Created by AugustRush on 2017/8/10.
//  Copyright © 2017年 August. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BICollectionViewFixedSizeLayout : UICollectionViewLayout

@property (nonatomic) CGSize itemSize;
@property (nonatomic) NSUInteger numberOfLinesPerPage;
@property (nonatomic) UIEdgeInsets contentInsets;
@property (nonatomic) CGFloat minimalColumnSpacing;
@property (nonatomic) BOOL anchorLastItemPerPage;

- (BOOL)isLastItemPerPageAtIndexPath:(NSIndexPath *)indexPath;

@end

