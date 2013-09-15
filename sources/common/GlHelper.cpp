#include "GlHelper.h"
#include "Log.h"

#include <memory>

GLuint GlHelper::compile(const char* src, GLenum type) {
    GLuint shader = glCreateShader(type);
    if (!shader) {
        return 0;
    }

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        GLint infoLen;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            auto info = std::unique_ptr<char[]>(new char[infoLen]);
            glGetShaderInfoLog(shader, infoLen, nullptr, info.get());
            Log::info(info.get());
        }

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint GlHelper::link(GLuint vertexShader, GLuint fragmentShader) {
    GLuint program = glCreateProgram();
    if (!program) {
        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {
        GLint infoLen ;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1) {
            auto info = std::unique_ptr<char[]>(new char[infoLen]);
            glGetProgramInfoLog(program, infoLen, nullptr, info.get());
            Log::info(info.get());
        }

        glDeleteProgram(program);
        return 0;
    }

    return program;
}
