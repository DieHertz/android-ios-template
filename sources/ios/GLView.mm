#import "GLView.h"
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "Application.h"
#include <TouchEvent.h>

@implementation GLView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        [self setupDisplayLink];
        Application::getInstance()->onSurfaceCreated();
        Application::getInstance()->onResize(frame.size.width, frame.size.height);
        self.multipleTouchEnabled = YES;
    }
    return self;
}

- (void)render:(CADisplayLink*)displayLink {
    Application::getInstance()->onUpdate();
    Application::getInstance()->onDraw();
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink *displayLink = [CADisplayLink displayLinkWithTarget:self
                                                             selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)setupLayer {
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

- (void)setupRenderBuffer {
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
                          self.frame.size.width, self.frame.size.height);
}

- (void)setupFrameBuffer {
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, _depthRenderBuffer);
}

#pragma mark Touches

- (void)onTouches:(NSSet*)touches withType:(TouchEvent::Type)touchEventType {
    NSArray *sortedTouches = [[touches allObjects] sortedArrayUsingSelector:@selector(timestamp)];
    for (int i = 0; i < sortedTouches.count; i++) {
        UITouch *touch = [sortedTouches objectAtIndex:i];
        CGPoint p = [touch locationInView:self];
        Application::getInstance()->onTouch(TouchEvent(p.x, p.y, touchEventType, i));
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [self onTouches:touches withType:TouchEvent::Down];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    [self onTouches:touches withType:TouchEvent::Move];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    [self onTouches:touches withType:TouchEvent::Cancel];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [self onTouches:touches withType:TouchEvent::Up];
}

- (void)dealloc
{
    [_context release];
    [super dealloc];
}

@end
