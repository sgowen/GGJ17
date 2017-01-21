//
//  ViewController.m
//  ggj17
//
//  Created by Stephen Gowen on 9/5/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#import "ViewController.h"

#import "ScreenController.h"

// C++
#include "MainScreen.h"
#include "InputManager.h"

@interface ViewController ()
{
    ScreenController *_screenController;
}

@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
        return;
    }
    
    GLKView *view = (GLKView *)self.view;
    
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.userInteractionEnabled = YES;
    [view setMultipleTouchEnabled:YES];
    
    self.preferredFramesPerSecond = 60;
    
    [EAGLContext setCurrentContext:self.context];
    
    CGRect screenBounds = [[UIScreen mainScreen] nativeBounds];
    
    CGSize size = CGSizeMake(screenBounds.size.width, screenBounds.size.height);
    size.width = roundf(size.width);
    size.height = roundf(size.height);
    
    NSLog(@"dimension %f x %f", size.width, size.height);
    
    [view bindDrawable];
    
    MainScreen *screen = new MainScreen();
    screen->createDeviceDependentResources();
    screen->createWindowSizeDependentResources(MAX(size.width, size.height), MIN(size.width, size.height), [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    
    _screenController = [[ScreenController alloc] initWithScreen:screen];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPause)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onResume)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    [_screenController resume];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self onPause];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    INPUT_MANAGER->onTouch(DOWN, pos.x, pos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    INPUT_MANAGER->onTouch(DRAGGED, pos.x, pos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    INPUT_MANAGER->onTouch(UP, pos.x, pos.y);
}

#pragma mark <GLKViewControllerDelegate>

- (void)update
{
    [_screenController update:self.timeSinceLastUpdate];
}

#pragma mark <GLKViewDelegate>

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    [_screenController present];
}

#pragma mark Private

- (void)onResume
{
    [_screenController resume];
}

- (void)onPause
{
    [_screenController pause];
}

@end
