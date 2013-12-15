#ifndef Gl_h
#define Gl_h

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#else
#include <OpenGLES/ES2/gl.h>
#endif

#define glsl(src) "#version 100\n" # src

#endif /* Gl_h */
