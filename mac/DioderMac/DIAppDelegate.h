//
//  DIAppDelegate.h
//  DioderMac
//
//  Created by Max Winde on 22.02.13.
//  Copyright (c) 2013 Max Winde. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <ORSSerialPort/ORSSerialPort.h>

@interface DIAppDelegate : NSObject <NSApplicationDelegate, ORSSerialPortDelegate>

@property (assign) IBOutlet NSWindow *window;

@property (weak) IBOutlet NSColorWell *dioder0Color;
@property (weak) IBOutlet NSColorWell *dioder1Color;

- (IBAction)colorDidChange:(id)sender;

@end
