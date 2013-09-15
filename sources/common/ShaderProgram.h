#ifndef ShaderProgram_h
#define ShaderProgram_h

#include "RenderDevice.h"

#include <string>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vSrc, const std::string& fSrc);
    ~ShaderProgram();

    void use();

    GLuint get() const;

private:
    GLuint mVertexShader;
    GLuint mFragmentShader;
    GLuint mProgram;
};

#endif /* ShaderProgram_h */
