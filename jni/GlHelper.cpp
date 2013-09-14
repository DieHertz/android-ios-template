#include "GlHelper.h"
#include "Log.h"

#include <memory>

GLuint GlHelper::createShader(const char* src, GLenum type) {
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
