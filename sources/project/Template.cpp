#include "Template.h"

#include <Gl.h>
#include <RenderDevice.h>
#include <ShaderProgram.h>
#include <Log.h>

#include <memory>

std::unique_ptr<ShaderProgram> pProgram;
static GLint positionLoc;
static GLint colorLoc;

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

    pProgram = std::unique_ptr<ShaderProgram>(new ShaderProgram(vShaderSrc, fShaderSrc));

    positionLoc = pProgram->getAttribLocation("aPosition");
    colorLoc = pProgram->getAttribLocation("aColor");

    glEnable(GL_SCISSOR_TEST);

    RenderDevice::clearColor(0.65f, 0.35f, 0.54f, 1);
}

void Template::onResize(const int width, const int height) {
    RenderDevice::viewport(0, 0, width, height);
}

void Template::onDraw() {
    RenderDevice::clear();

    RenderDevice::begin(*pProgram.get());

    GLfloat vertices[] {
        -0.75f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f
    };
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLoc);
    
    GLfloat colors[] {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(colorLoc);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

bool Template::onBackPressed() {
    Log::info("%s", __FUNCTION__);
    return true;
}
