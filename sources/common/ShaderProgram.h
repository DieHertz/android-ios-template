#ifndef ShaderProgram_h
#define ShaderProgram_h

#include "Gl.h"

#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vSrc, const std::string& fSrc);
    ~ShaderProgram();

    void use() const;

    GLuint get() const;
    GLint getAttribLocation(const char* attribName) const;
    GLint getUniformLocation(const char* uniformName) const;

private:
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mProgram;
};

#endif /* ShaderProgram_h */
