#ifndef GlHelper_h
#define GlHelper_h

#include "RenderDevice.h"

class GlHelper {
    GlHelper() = delete;
    GlHelper(const GlHelper&) = delete;

public:
    static GLuint compile(const char* src, GLenum type);
    static GLuint link(GLuint vertexShader, GLuint fragmentShader);
};

#endif /* GlHelper_h */
