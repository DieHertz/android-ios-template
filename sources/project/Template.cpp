#include "Template.h"

#include <Gl.h>
#include <RenderDevice.h>
#include <Log.h>

#include <cmath>

Template::Template() : mTime(0) {

}

void Template::onContextCreated() {
    Log::info("%s: %s", __FUNCTION__, glGetString(GL_VERSION));

    const char* vShaderSrc {
        "#version 100\n"

        "attribute vec2 aPosition;"
        "attribute vec3 aColor;"

        "uniform mat4 uModelViewProjection;"
        "uniform mat4 uModelView;"

        "varying vec3 vColor;"

        "void main() {"
            "gl_Position = uModelViewProjection * vec4(aPosition, 0, 1);"
            "vColor = aColor;"
        "}"
    };

    const char* fShaderSrc {
        "#version 100\n"

        "precision mediump float;"

        "varying vec3 vColor;"

        "void main() {"
            "gl_FragColor = vec4(vColor, 1);"
        "}"
    };

    mProgram = std::unique_ptr<ShaderProgram>(new ShaderProgram(vShaderSrc, fShaderSrc));

    RenderDevice::clearColor(0.65f, 0.35f, 0.54f, 1);
}

void Template::onContextLost() {
    mProgram.reset();
}

void Template::onResize(const int width, const int height) {
    RenderDevice::viewport(0, 0, width, height);
}

void Template::onUpdate(const float delta) {
    mTime += delta;
}

void Template::onDraw() {
    RenderDevice::clear();

    RenderDevice::begin(*mProgram.get());

    const auto offset = 0.25f * std::sin(mTime);
    GLfloat vertices[] {
        -0.75f, 0.5f,
        0.5f, 0.5f + offset,
        0.5f, -0.5f - offset
    };
    auto positionLoc = mProgram->getAttribLocation("aPosition");
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLoc);
    
    GLfloat colors[] {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    auto colorLoc = mProgram->getAttribLocation("aColor");
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(colorLoc);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glFlush();
}

bool Template::onBackPressed() {
    return true;
}
