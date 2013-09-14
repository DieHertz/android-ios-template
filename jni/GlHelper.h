#ifndef GlHelper_h
#define GlHelper_h

#include "RenderDevice.h"

class GlHelper {
    GlHelper() = delete;
    GlHelper(const GlHelper&) = delete;

public:
    static GLuint createShader(const char* src, GLenum type);
};

#endif /* GlHelper_h */
