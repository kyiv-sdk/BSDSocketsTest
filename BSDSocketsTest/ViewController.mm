//
//  ViewController.m
//  BSDSocketsTest
//
//  Created by Oleksandr Hordiienko on 1/9/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#import "ViewController.h"
#import "IBSDSocketDelegate.hpp"

__weak ViewController *refToSelf;
void IBSDSocketDelegate::didReceiveMessage(std::string message) {
    [refToSelf didReceiveMessage:[NSString stringWithCString:message.c_str() encoding:[NSString defaultCStringEncoding]]];
}

@implementation ViewController {
    BSDClientSocket *client;
    BSDServerSocket *server;
    IBSDSocketDelegate *delegate;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    refToSelf = self;
    
    int port = 9090;
    delegate = new IBSDSocketDelegate();
    
    /* --- Exapmple of (JSON -> const char *) ---  */
    NSDictionary<NSString *, id> *json = @{ @"message": @"Here is simple JSON-object" };
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:json options:0 error:nil];
    const char *jsonMsg = [[[NSString alloc] initWithData:jsonData encoding: NSUTF8StringEncoding] UTF8String];
    
    /* --- Exapmple ServerSocket creation ---  */
    server = new BSDServerSocket(port, delegate);
    server->start();
    
    /* --- Exapmple ClientSocket creation ---  */
    client = new BSDClientSocket(port);
    client->start();
    
    /* --- Exapmple ClientSocket using ---  */
    sleep(1);
    client->sendData("Here is simple message");
    sleep(1);
    client->sendData(jsonMsg);
}


- (void)dealloc {
    /* --- Exapmple Socket closing ---  */
    client->closeSocket();
    server->closeSocket();
}


/* --- This method will be called when Server or Delegate will receive message --- */
- (void)didReceiveMessage:(NSString *)message {
    // TODO: Handle received message
    NSLog(@"--------MESSAGE--------");
    NSLog(@"%@", message);
    NSLog(@"--------MESSAGE--------");
}

@end
