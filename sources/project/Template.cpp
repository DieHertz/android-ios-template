#include "Template.h"
#include "Model.h"

#include <RenderDevice.h>
#include <Log.h>
#include <TouchEvent.h>

Template::Template() {
    reset();
}

void Template::onContextCreated() {
    Log::info("%s: %s", __FUNCTION__, glGetString(GL_VERSION));

    const char* vShaderSrc {
        "#version 100\n"

        "attribute vec3 aPosition;"

        "uniform mat4 uModelViewProjection;"
        "uniform mat4 uModelView;"

        "void main() {"
            "gl_Position = uModelViewProjection * vec4(aPosition, 1);"
        "}"
    };

    const char* fShaderSrc {
        "#version 100\n"

        "precision mediump float;"

        "void main() {"
            "gl_FragColor = vec4(0.6, 0.4, 0.3, 1) * vec4(gl_FragCoord.w * 0.4, gl_FragCoord.w * 0.4, gl_FragCoord.w * 0.4, 1);"
        "}"
    };

    mProgram = std::unique_ptr<ShaderProgram>(new ShaderProgram(vShaderSrc, fShaderSrc));

    RenderDevice::clearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Template::onContextLost() {
    mProgram.reset();
}

void Template::onResize(const int width, const int height) {
    RenderDevice::viewport(0, 0, width, height);
    RenderDevice::lookAt(mEx, mEy, mEz,
                         0, 0, 0,
                         0, 1, 0);
    RenderDevice::perspective(85.0f, static_cast<float>(width) / height, 0.1f, 5.0f);
}

void Template::onUpdate(const float delta) {
    mTime += delta;

    if (mTimer > 0) {
        mTimer -= delta;
    }
}

void Template::onDraw() {
    RenderDevice::clear();

    if (wireframe) {
        RenderDevice::drawLine(reinterpret_cast<const float*>(&mLines[0]),
                                    nullptr,
                mLines.size() * 2, *mProgram.get());
    } else {
        RenderDevice::drawTriangles(reinterpret_cast<const float*>(&mTriangles[0]),
            nullptr, nullptr,
            mTriangles.size() * 3, *mProgram.get());
    }
}

void Template::onTouch(const TouchEvent& event) {
    if (event.getType() == TouchEvent::Down) {
        if (mTimer > 0) {
            subdiv();
            return;
        }
        mX = event.getX();
        mY = event.getY();

        mTimer = 0.5f;
    } else if (event.getType() == TouchEvent::Move) {
        mEx += (event.getX() - mX) * 0.01f;
        mEz += (event.getY() - mY) * 0.01f;
        RenderDevice::lookAt(mEx, mEy, mEz,
                             0, 0, 0,
                             0, 1, 0);
        mX = event.getX();
        mY = event.getY();
    }
}

bool Template::onBackPressed() {
    reset();

    return true;
}

void Template::reset() {
    std::vector<Triangle> triangles;

    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { 0.1f, 0.1f, -0.1f }, { 0.1f, -0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { 0.1f, 0.1f, -0.1f }, { -0.1f, 0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, 0.1f, -0.1f }, { 0.1f, 0.1f, 0.1f }, { 0.1f, 0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, 0.1f, -0.1f }, { 0.1f, 0.1f, 0.1f }, { -0.1f, 0.1f, 0.1f } });
    triangles.push_back({ { 0.1f, -0.1f, -0.1f }, { 0.1f, 0.1f, 0.1f }, { 0.1f, -0.1f, 0.1f } });
    triangles.push_back({ { 0.1f, -0.1f, -0.1f }, { 0.1f, 0.1f, 0.1f }, { 0.1f, 0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { 0.1f, -0.1f, 0.1f }, { -0.1f, -0.1f, 0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { 0.1f, -0.1f, 0.1f }, { 0.1f, -0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { -0.1f, 0.1f, 0.1f }, { -0.1f, 0.1f, -0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, -0.1f }, { -0.1f, 0.1f, 0.1f }, { -0.1f, -0.1f, 0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, 0.1f }, { 0.1f, 0.1f, 0.1f }, { -0.1f, 0.1f, 0.1f } });
    triangles.push_back({ { -0.1f, -0.1f, 0.1f }, { 0.1f, 0.1f, 0.1f }, { 0.1f, -0.1f, 0.1f } });

    mTriangles.swap(triangles);

    createLine();
}

void Template::subdiv() {
    std::vector<Triangle> newTriangles;
    for (auto& t : mTriangles) {
        auto mid = (t.a + t.b) / 2;
        mid = mid * length(t.a) / length(mid);
        newTriangles.push_back({ t.a, t.c, mid });
        newTriangles.push_back({ t.b, t.c, mid });
    }

    mTriangles.swap(newTriangles);

    createLine();
}

void Template::createLine() {
    std::vector<Line> lines;
    lines.reserve(mTriangles.size() * 3);

    for (auto& t : mTriangles) {
        lines.push_back({ t.a, t.b });
        lines.push_back({ t.b, t.c });
        lines.push_back({ t.c, t.a });
    }

    mLines.swap(lines);
}
