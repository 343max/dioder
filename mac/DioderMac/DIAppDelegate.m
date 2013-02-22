//
//  DIAppDelegate.m
//  DioderMac
//
//  Created by Max Winde on 22.02.13.
//  Copyright (c) 2013 Max Winde. All rights reserved.
//

#import "DIAppDelegate.h"

@interface DIAppDelegate ()

@property (strong) ORSSerialPort *serialPort;
@property (strong) NSTimer *sendColorTimer;

- (void)setColor:(NSColor *)color ofDioder:(NSUInteger)dioderIndex;
- (void)sendColors;

@end


@implementation DIAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    self.serialPort = [[ORSSerialPort alloc] initWithPath:@"/dev/tty.usbmodemfa131"];
    self.serialPort.baudRate = @(57600);
    self.serialPort.delegate = self;
    [self.serialPort open];
    
    self.sendColorTimer = [NSTimer scheduledTimerWithTimeInterval:1.0
                                                           target:self
                                                         selector:@selector(sendColors)
                                                         userInfo:nil
                                                          repeats:YES];
}

- (void)applicationWillTerminate:(NSNotification *)notification;
{
    [self.serialPort close];
}

- (void)setColor:(NSColor *)color ofDioder:(NSUInteger)dioderIndex;
{
    char bytes[4];
    bytes[0] = (char)dioderIndex;
    bytes[1] = (char)(color.redComponent * 255.0);
    bytes[2] = (char)(color.greenComponent * 255.0);
    bytes[3] = (char)(color.blueComponent * 255.0);
    NSLog(@"color: %f, %f, %f", color.redComponent, color.greenComponent, color.blueComponent);
    NSData *data = [[NSData alloc] initWithBytes:&bytes length:sizeof(bytes)];
    
    [self.serialPort sendData:data];
}

- (void)sendColors;
{
    [self setColor:self.dioder0Color.color ofDioder:0];
    [self setColor:self.dioder1Color.color ofDioder:1];
}

- (void)colorDidChange:(NSColorWell *)sender;
{
    NSUInteger dioderIndex = (sender == self.dioder0Color ? 0 : 1);
    [self setColor:sender.color ofDioder:dioderIndex];
}

#pragma mark ORSSerialPortDelegate

- (void)serialPortWasOpened:(ORSSerialPort *)serialPort;
{
    NSLog(@"serialPortWasOpened: %@", serialPort);
    
    double delayInSeconds = 0.3;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self setColor:self.dioder0Color.color ofDioder:0];
        [self setColor:self.dioder1Color.color ofDioder:1];
    });
}

- (void)serialPort:(ORSSerialPort *)serialPort didReceiveData:(NSData *)data;
{
    NSString *stringData = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
    NSLog(@"d: %@", stringData);
}

- (void)serialPortWasRemovedFromSystem:(ORSSerialPort *)serialPort;
{
    NSLog(@"---- Serial PortWasRemovedFromSystem: %@", serialPort);
}

@end
