//
//  ViewController.m
//  TCPSocketClient
//
//  Created by scasy_wang on 16/10/20.
//  Copyright © 2016年 scasy_wang. All rights reserved.
//

#import "ViewController.h"
#import "AsyncSocket.h"
@interface ViewController ()<AsyncSocketDelegate>
@property(nonatomic,strong)AsyncSocket *tcpScoket;
@property (weak, nonatomic) IBOutlet UITextField *hostTF;
@property (weak, nonatomic) IBOutlet UITextField *portTF;
@property (weak, nonatomic) IBOutlet UITextView *textV;
@property (weak, nonatomic) IBOutlet UITextField *sendTF;

@property (nonatomic, strong) NSMutableArray *connectHostMuArr;
@property (nonatomic, strong) NSArray *sendHostArr;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.connectHostMuArr = [NSMutableArray array];
    self.hostTF.text = @"192.168.3.105";
    self.portTF.text = @"8888";
    self.tcpScoket = [[AsyncSocket alloc]initWithDelegate:self];
    
    // Do any additional setup after loading the view, typically from a nib.
}

- (IBAction)doConnect:(id)sender {
    
    NSError *error;
    BOOL isConnect = [self.tcpScoket connectToHost:self.hostTF.text onPort:[self.portTF.text intValue] withTimeout:-1 error:&error];
    if (isConnect) {
        NSLog(@"连接成功");
    }else {
        NSLog(@"连接失败");
    }
    
    //    [self.tcpScoket setRunLoopModes:[NSArray arrayWithObject:NSRunLoopCommonModes]];
    [self.tcpScoket readDataWithTimeout:-1 tag:0];
   
}

- (IBAction)doSend:(id)sender {
    [self.view endEditing:YES];
    NSData *data = [self.sendTF.text dataUsingEncoding:NSUTF8StringEncoding];
    [self.tcpScoket writeData:data withTimeout:-1 tag:0];
   
}
-(void)addMessage:(NSString *)str{
    self.textV.text = [self.textV.text stringByAppendingFormat:@"%@\n\n\n",str];
    [self.textV scrollRangeToVisible:[self.textV.text rangeOfString:str options:NSBackwardsSearch]];
}
//AsyncSocketDelegate
//已经连接上
-(void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port{
    
    [self addMessage:[NSString stringWithFormat:@"连接上%@\nlocal:%@",host,sock]];
    [self.connectHostMuArr addObject:host];
    
    [self.tcpScoket readDataWithTimeout:-1 tag:0];
}
-(void)onSocketDidDisconnect:(AsyncSocket *)sock{
    //    [self addMessage:[NSString stringWithFormat:@"%d断开连接:%@ ",a,sock]];
}
-(void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag{
    NSString *msg = [[NSString alloc] initWithData: data encoding:NSUTF8StringEncoding];
    NSLog(@"读到的数据：%@",msg);
    [self addMessage:[NSString stringWithFormat:@"收到数据：%@",msg]];
    [self.tcpScoket readDataWithTimeout: -1 tag: 0];
}
-(void)onSocket:(AsyncSocket *)sock didWriteDataWithTag:(long)tag{
//    [self addMessage:[NSString stringWithFormat:@"发送了"]];
}

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self.view endEditing:YES];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

