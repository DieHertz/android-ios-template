#ifndef GlHelper_h
#define GlHelper_h

#include "Gl.h"

class GlHelper {
    GlHelper() = delete;

public:
    static GLuint compile(const char* src, GLenum type);
    static GLuint link(GLuint vertexShader, GLuint fragmentShader);
};

#endif /* GlHelper_h */
