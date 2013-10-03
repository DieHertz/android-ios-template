#ifndef RenderDevice_h
#define RenderDevice_h

#include "Gl.h"

#include <glm/glm.hpp>

class ShaderProgram;

class RenderDevice {
    RenderDevice() = delete;
    RenderDevice(const RenderDevice&) = delete;

public:
    static void clearColor(const float r, const float g, const float b, const float a);
    static void clear();
    static void viewport(const float x, const float y, const float w, const float h);
    static void lookAt(const float ex, const float ey, const float ez,
                       const float cx, const float cy, const float cz,
                       const float ux, const float uy, const float uz);
    static void perspective(const float fovy, const float aspect,
                            const float zNear, const float zFar);

    static void begin(const ShaderProgram& program);

    static void draw(const GLuint vbo, const int points, const GLenum type,
                     const ShaderProgram& program);
    static void draw(const float* vertices, const int points, const GLenum type,
                     const ShaderProgram& program);

private:
    static glm::mat4 model;
    static glm::mat4 view;
    static glm::mat4 projection;
    static glm::mat4 modelView;
    static glm::mat4 modelViewProjection;
};

#endif /* RenderDevice_h */
