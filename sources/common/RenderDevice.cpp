#include "RenderDevice.h"
#include "ShaderProgram.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const ShaderProgram* RenderDevice::program = nullptr;
glm::mat4 RenderDevice::model;
glm::mat4 RenderDevice::view;
glm::mat4 RenderDevice::projection;
glm::mat4 RenderDevice::modelView;
glm::mat4 RenderDevice::modelViewProjection;

void RenderDevice::clearColor(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RenderDevice::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderDevice::viewport(const float x, const float y, const float w, const float h) {
    glViewport(x, y, w, h);
}

void RenderDevice::lookAt(const float ex, const float ey, const float ez,
                   const float cx, const float cy, const float cz,
                   const float ux, const float uy, const float uz) {
    view = glm::lookAt(glm::vec3(ex, ey, ez), glm::vec3(cx, cy, cz),
                       glm::vec3(ux, uy, uz));
    modelView = view * model;
    modelViewProjection = projection * modelView;
}

void RenderDevice::perspective(const float fovy, const float aspect,
                        const float zNear, const float zFar) {
    projection = glm::perspective(fovy, aspect, zNear, zFar);
    modelViewProjection = projection * modelView;
}

void RenderDevice::translate(const float x, const float y, const float z) {
    auto transformation(glm::translate(glm::mat4(), glm::vec3(x, y, z)));
    
    model = model * transformation;
    modelView = modelView * transformation;
    modelViewProjection = modelViewProjection * transformation;

    if (program) {
        auto mvLoc = program->getUniformLocation("uModelView");
        auto mvpLoc = program->getUniformLocation("uModelViewProjection");

        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(modelView));
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
    }
}

void RenderDevice::begin(const ShaderProgram* program) {
    RenderDevice::program = program;
    program->use();

    auto mvLoc = program->getUniformLocation("uModelView");
    auto mvpLoc = program->getUniformLocation("uModelViewProjection");

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(modelView));
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(modelViewProjection));
}

void RenderDevice::end() {
    glUseProgram(0);
    program = nullptr;
}

void RenderDevice::draw(const GLuint vbo, const int points, const GLenum type) {
    auto positionLoc = program->getAttribLocation("aPosition");
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(positionLoc);

    glDrawArrays(type, 0, points);

    glDisableVertexAttribArray(positionLoc);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderDevice::draw(const float* vertices, const int points, const GLenum type) {
    auto positionLoc = program->getAttribLocation("aPosition");
    glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLoc);

    glDrawArrays(type, 0, points);

    glDisableVertexAttribArray(positionLoc);
}
