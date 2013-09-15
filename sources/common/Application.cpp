#include "Application.h"
#include "RenderDevice.h"
#include "ShaderProgram.h"
#include "Log.h"

#include <memory>

std::unique_ptr<ShaderProgram> pProgram;
static GLint positionLoc;
static GLint colorLoc;

void Application::onCreate() {
    Log::info("%s", __FUNCTION__);
}

void Application::onContextCreated() {
    Log::info("%s: %s", __FUNCTION__, glGetString(GL_VERSION));

    const char* vShaderSrc {
        "#version 100\n"

        "attribute vec2 aPosition;"
        "attribute vec3 aColor;"

        "varying vec3 vColor;"

        "void main() {"
            "gl_Position = vec4(aPosition, 0, 1);"
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

    positionLoc = glGetAttribLocation(pProgram->get(), "aPosition");
    colorLoc = glGetAttribLocation(pProgram->get(), "aColor");

    glEnable(GL_SCISSOR_TEST);
}

void Application::onResize(const int width, const int height) {
    glViewport(width / 4, height / 4, width / 2, height / 2);
    glScissor(width / 4, height / 4, width / 2, height / 2);
}

void Application::onUpdate() {

}

void Application::onDraw() {
    glClearColor(0.63f, 0.35f, 0.54f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    pProgram->use();

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

void Application::onTouch(const TouchEvent& event) {

}

bool Application::onBackPressed() {
    Log::info("%s", __FUNCTION__);
    return true;
}
