#include "RenderDevice.h"
#include "ShaderProgram.h"
#include "Gl.h"

void RenderDevice::clearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RenderDevice::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderDevice::viewport(const float x, const float y, const float w, const float h) {
    glViewport(x, y, w, h);
}

void RenderDevice::begin(const ShaderProgram& program) {
    program.use();

    auto mvLoc = program.getUniformLocation("uModelView");
    auto mvpLoc = program.getUniformLocation("uModelViewProjection");

    float matrix[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &matrix[0]);
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &matrix[0]);
}
