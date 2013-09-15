//
//  GLView.h
//  OpenGL_Test
//
//  Created by Sachs on 07.02.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include "Application.h"

@interface GLView : UIView {
    CAEAGLLayer *_eaglLayer;
    EAGLContext *_context;
    GLuint _colorRenderBuffer;
    GLuint _depthRenderBuffer;
    Application *_application;
}

- (id)initWithFrame:(CGRect)frame application:(Application*)application;

@end
