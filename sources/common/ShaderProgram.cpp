#include "ShaderProgram.h"
#include "GlHelper.h"

ShaderProgram::ShaderProgram(const std::string& vSrc, const std::string& fSrc)
: mVertexShader(0), mFragmentShader(0), mProgram(0) {
    mVertexShader = GlHelper::compile(vSrc.c_str(), GL_VERTEX_SHADER);
    mFragmentShader = GlHelper::compile(fSrc.c_str(), GL_FRAGMENT_SHADER);
    mProgram = GlHelper::link(mVertexShader, mFragmentShader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(mProgram);
    glDeleteShader(mFragmentShader);
    glDeleteShader(mVertexShader);
}

void ShaderProgram::use() const {
    glUseProgram(mProgram);
}

GLuint ShaderProgram::get() const {
    return mProgram;
}

GLint ShaderProgram::getAttribLocation(const char* attribName) const {
    return glGetAttribLocation(mProgram, attribName);
}

GLint ShaderProgram::getUniformLocation(const char* uniformName) const {
    return glGetUniformLocation(mProgram, uniformName);
}
