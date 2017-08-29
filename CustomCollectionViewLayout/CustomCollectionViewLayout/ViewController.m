//
//  ViewController.m
//  CustomCollectionViewLayout
//
//  Created by AugustRush on 2017/8/10.
//  Copyright © 2017年 August. All rights reserved.
//

#import "ViewController.h"
#import "BICollectionViewFixedSizeLayout.h"
#import "BICollectionViewStackLayout.h"

@interface ViewController ()<UICollectionViewDataSource,UICollectionViewDelegate,BICollectionViewStackLayoutDelegate>

@property (nonatomic, readonly) BICollectionViewFixedSizeLayout *emojiLayout;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.collectionView.pagingEnabled = YES;
    [self.collectionView registerClass:[UICollectionViewCell class] forCellWithReuseIdentifier:@"cell"];
//    self.emojiLayout.anchorLastItemPerPage = YES;
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BICollectionViewFixedSizeLayout *)emojiLayout {
    return (BICollectionViewFixedSizeLayout *)self.collectionView.collectionViewLayout;
}

#pragma mark - stack layout delegate methods

- (CGSize)stackLayout:(BICollectionViewStackLayout *)stackLayout sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
//    return CGSizeMake(60, 50);
    return CGSizeMake(40 + (indexPath.row % 3) * (CGRectGetWidth(self.view.bounds) / 5.0) - 10, 50);
}

#pragma mark - UICollectionViewDataSource methods

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    static NSUInteger i = 0;
    NSUInteger count = 100 * (i + 1);
    count++;
    return count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    
    cell.backgroundColor = [UIColor redColor];
    return cell;
}

#pragma mark - 

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    [collectionView.collectionViewLayout invalidateLayout];
    if ([collectionView.collectionViewLayout isKindOfClass:[BICollectionViewFixedSizeLayout class]]) {
        [UIView performWithoutAnimation:^{
            BICollectionViewStackLayout *stackLayout = [[BICollectionViewStackLayout alloc] init];
            [collectionView setCollectionViewLayout:stackLayout animated:NO];
        }];
    } else {
        [UIView performWithoutAnimation:^{
            BICollectionViewFixedSizeLayout *stackLayout = [[BICollectionViewFixedSizeLayout alloc] init];
            stackLayout.itemSize = CGSizeMake(arc4random() % 50 + 40, arc4random() % 50 + 40);
            stackLayout.numberOfLinesPerPage = 2 + arc4random() % 3;
            [collectionView setCollectionViewLayout:stackLayout animated:NO];
        }];
    }
    [collectionView reloadData];
//    [collectionView setContentOffset:CGPointZero];
}

@end
