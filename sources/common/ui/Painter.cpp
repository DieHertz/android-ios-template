#include "Painter.h"
#include "Gl.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace {
    const auto vSrc = glsl(
        attribute vec2 aPosition;
        attribute vec4 aColor;

        uniform mat4 uTransform;
        uniform bool uFillColor;
        uniform vec4 uColor;

        varying vec4 vColor;

        void main() {
            gl_Position = uTransform * vec4(aPosition, 0, 1);
            if (uFillColor) {
                vColor = uColor;
            } else {
                vColor = aColor;
            }
        }
    );

    const auto fSrc = glsl(
        precision mediump float;

        varying vec4 vColor;

        void main() {
            gl_FragColor = vColor;
        }
    );
}

Painter::Painter() : _shader(vSrc, fSrc) {

}

void Painter::drawRect(const Rect& r, const Color& c) {
    _shader.use();

    const float x = r.x;
    const float y = r.y;
    const float w = r.w;
    const float h = r.h;

    const GLfloat vertices[] {
        x, y,
        x, y + h,
        x + w, y + h,
        x + w, y + h,
        x + w, y,
        x, y
    };

    const auto positionLoc = _shader.getAttribLocation("aPosition");
    glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionLoc);

    glUniformMatrix4fv(_shader.getUniformLocation("uTransform"), 1, GL_FALSE,
        glm::value_ptr(_transformStack.top()));
    glUniform1i(_shader.getUniformLocation("uFillColor"), true);
    glUniform4fv(_shader.getUniformLocation("uColor"), 1, reinterpret_cast<const GLfloat*>(&c));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(positionLoc);
}

void Painter::setRootTransform(const Rect& r) {
    clearTransformStack();
    _transformStack.push(glm::ortho(static_cast<float>(r.x), static_cast<float>(r.x + r.w),
        static_cast<float>(r.y + r.h), static_cast<float>(r.y),
        -1.0f, 1.0f));
}

void Painter::clearTransformStack() {
    decltype(_transformStack) dump;
    _transformStack.swap(dump);
}

void Painter::pushTransform(const Point& p) {
    _transformStack.push(glm::translate(_transformStack.top(), glm::vec3(p.x, p.y, 0)));
}

void Painter::popTransform() {
    _transformStack.pop();
}
