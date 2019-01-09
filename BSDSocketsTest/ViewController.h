//
//  ViewController.h
//  BSDSocketsTest
//
//  Created by Oleksandr Hordiienko on 1/9/19.
//  Copyright © 2019 SoftServe. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BSDServerSocket.hpp"
#import "BSDClientSocket.hpp"
#import "IBSDSocketDelegate.hpp"

@interface ViewController : UIViewController

- (void)didReceiveMessage:(NSString *)message;

@end

