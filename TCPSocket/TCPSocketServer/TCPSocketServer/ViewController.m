//
//  ViewController.m
//  TCPSocketServer
//
//  Created by scasy_wang on 16/10/20.
//  Copyright © 2016年 scasy_wang. All rights reserved.
//

#import "ViewController.h"
#import "AsyncSocket.h"
@interface ViewController ()<AsyncSocketDelegate>
@property (weak, nonatomic) IBOutlet UILabel *localHostLab;
@property (weak, nonatomic) IBOutlet UITextField *portTF;
@property (weak, nonatomic) IBOutlet UITextView *textV;
@property (weak, nonatomic) IBOutlet UITextField *responseTF;
@property(nonatomic,strong)AsyncSocket *tcpScoket;
@property (nonatomic, strong) NSMutableArray *clientSocketMuArr;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.clientSocketMuArr = [NSMutableArray array];
    self.tcpScoket = [[AsyncSocket alloc]initWithDelegate:self];
    
    self.portTF.text = @"8888";
//    NSError *error;
//    [self.tcpScoket acceptOnPort:[self.portTF.text intValue] error:&error];
//    self.localHostLab.text = [self.localHostLab.text stringByAppendingString:[self.tcpScoket localHost]];
    
    
    // Do any additional setup after loading the view, typically from a nib.
}
- (IBAction)doMonitor:(id)sender {
    NSError *error;
    [self.tcpScoket acceptOnPort:[self.portTF.text intValue] error:&error];
    [self addMessage:@"已监听！。。。。。"];
//    self.localHostLab.text = [self.localHostLab.text stringByAppendingString:[self.tcpScoket localHost]];

}
- (IBAction)doResponse:(id)sender {
    NSData *data = [self.responseTF.text dataUsingEncoding:NSUTF8StringEncoding];
    [self.tcpScoket writeData:data withTimeout:-1 tag:10];
    for (AsyncSocket *soc in self.clientSocketMuArr) {
        [soc writeData:data withTimeout:-1 tag:10];
    }
    
    [self.view endEditing:YES];
}
-(void)addMessage:(NSString *)str{
    self.textV.text = [self.textV.text stringByAppendingFormat:@"%@\n\n\n",str];
    [self.textV scrollRangeToVisible:[self.textV.text rangeOfString:str options:NSBackwardsSearch]];
}
#pragma mark - AsyncSocketDelegate
- (void)onSocket:(AsyncSocket *)sock didAcceptNewSocket:(AsyncSocket *)newSocket{
    
    [self.clientSocketMuArr addObject:newSocket];
    [newSocket readDataWithTimeout:-1 tag:0];
}
- (void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag{
    NSString *readStr = [[NSString alloc] initWithData: data encoding:NSUTF8StringEncoding];
    NSLog(@"读到的数据：%@",readStr);
    [self addMessage:[NSString stringWithFormat:@"读到的数据：%@ \nhost:%@", readStr, sock.connectedHost]];
    
//    [sock writeData:[readStr dataUsingEncoding:NSUTF8StringEncoding] withTimeout:-1 tag:101];
    
    [sock readDataWithTimeout:-1 tag:0];
    
}
-(void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port{
    [self addMessage:[NSString stringWithFormat:@"已连接%@",host]];
    self.localHostLab.text = [self.localHostLab.text stringByAppendingString:[sock localHost]];

}
-(void)onSocket:(AsyncSocket *)sock willDisconnectWithError:(NSError *)err{
    [self addMessage:[NSString stringWithFormat:@"willDisc:%@",sock]];
}
-(void)onSocketDidDisconnect:(AsyncSocket *)sock{
    [self addMessage:[NSString stringWithFormat:@"已断开:%@",sock]];
}
-(void)onSocket:(AsyncSocket *)sock didWriteDataWithTag:(long)tag{
    NSLog(@"sock:%@  %ld",sock,tag);
}
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event{
    [self.view endEditing:YES];
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
