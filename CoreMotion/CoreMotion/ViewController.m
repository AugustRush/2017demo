//
//  ViewController.m
//  CoreMotion
//
//  Created by AugustRush on 2017/4/26.
//  Copyright © 2017年 August. All rights reserved.
//

#import "ViewController.h"
#import <CoreMotion/CoreMotion.h>

@interface ViewController ()

@property (nonatomic, strong) CMMotionActivityManager *motionActivityManager;
@property (nonatomic, strong) NSDateFormatter *dateFormater;
@property (weak, nonatomic) IBOutlet UILabel *currentStateLabel;
@property (weak, nonatomic) IBOutlet UILabel *confidenceLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeStampLabel;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    if ([CMMotionActivityManager isActivityAvailable]) {
        self.motionActivityManager = [[CMMotionActivityManager alloc]init];
        self.dateFormater = [[NSDateFormatter alloc] init];
        self.dateFormater.dateFormat = @"yyyy-MM-dd HH:mm:ss";
        
        __weak typeof (self) weakSelf = self;
        [self.motionActivityManager startActivityUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:^(CMMotionActivity * _Nullable activity) {
            weakSelf.timeStampLabel.text = [weakSelf.dateFormater stringFromDate:[NSDate date]];
            
            if (activity.unknown) {
                weakSelf.currentStateLabel.text = @"未知狀態";
            } else if (activity.walking) {
                weakSelf.currentStateLabel.text = @"步行";
            } else if (activity.running) {
                weakSelf.currentStateLabel.text = @"跑步";
            } else if (activity.automotive) {
                weakSelf.currentStateLabel.text = @"駕車";
            } else if (activity.stationary) {
                weakSelf.currentStateLabel.text = @"靜止";
            }
            
            if (activity.confidence == CMMotionActivityConfidenceLow) {
                weakSelf.confidenceLabel.text = @"準確度  低";
            } else if (activity.confidence == CMMotionActivityConfidenceMedium) {
                weakSelf.confidenceLabel.text = @"準確度  中";
            } else if (activity.confidence == CMMotionActivityConfidenceHigh) {
                weakSelf.confidenceLabel.text = @"準確度  高";
            }
        }];

    } else {
        self.currentStateLabel.text = @"不可用......";
    }
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
