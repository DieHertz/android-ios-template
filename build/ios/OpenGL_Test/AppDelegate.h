//
//  AppDelegate.h
//  OpenGL_Test
//
//  Created by Sachs on 07.02.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"

class Application;
@class ViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    Application *app;
}

- (void)onContextCreated;
- (void)onDraw;

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) ViewController *viewController;
@property (nonatomic, retain) IBOutlet GLView *glView;

@end
