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

    glGenBuffers(1, &mTrianglesVbo);
    glGenBuffers(1, &mLinesVbo);
    fillVbo();

    RenderDevice::clearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Template::onContextLost() {
    mProgram.reset();
    mTrianglesVbo = 0;
    mLinesVbo = 0;
}

void Template::onResize(const int width, const int height) {
    RenderDevice::viewport(0, 0, width, height);
    RenderDevice::lookAt(mEye.x, mEye.y, mEye.z,
                         0, 0, 0,
                         mUp.x, mUp.y, mUp.z);
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
        RenderDevice::draw(mLinesVbo, mLines.size() * 2, GL_LINES, *mProgram.get());
    } else {
        RenderDevice::draw(mTrianglesVbo, mTriangles.size() * 3, GL_TRIANGLES, *mProgram.get());
    }
}

void Template::onTouch(const TouchEvent& event) {
    if (event.getType() == TouchEvent::Down) {
        if (mTimer > 0) {
            subdiv();
            fillVbo();
            return;
        }
        mX = event.getX();
        mY = event.getY();

        mTimer = 0.5f;
    } else if (event.getType() == TouchEvent::Move) {
        const float k = 1.0f;
        auto dx = k * (event.getX() - mX);
        auto dy = k * (event.getY() - mY);

        left(dx);
        up(-dy);

        RenderDevice::lookAt(mEye.x, mEye.y, mEye.z,
                             0, 0, 0,
                             mUp.x, mUp.y, mUp.z);
        mX = event.getX();
        mY = event.getY();
    }
}

bool Template::onBackPressed() {
    reset();
    fillVbo();

    return true;
}

void Template::fillVbo() {
    glBindBuffer(GL_ARRAY_BUFFER, mTrianglesVbo);
    glBufferData(GL_ARRAY_BUFFER, mTriangles.size() * sizeof(decltype(mTriangles)::value_type),
                 mTriangles.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mLinesVbo);
    glBufferData(GL_ARRAY_BUFFER, mLines.size() * sizeof(decltype(mLines)::value_type),
                 mLines.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void Template::up(const float degrees) {
    glm::vec3 ortho { glm::normalize(glm::cross(mEye, mUp)) };
    glm::vec4 eye4(mEye, 1.0f);
    glm::vec4 up4(mUp, 1.0f);

    eye4 = eye4 * glm::rotate(glm::mat4(), degrees, ortho);
    up4 = up4 * glm::rotate(glm::mat4(), degrees, ortho);

    mEye = glm::vec3(eye4);
    mUp = glm::vec3(up4);
}

void Template::left(const float degrees) {
    glm::vec4 eye4 {
        glm::vec4(mEye, 1.0f) * glm::rotate(glm::mat4(), degrees, mUp)
    };

    mEye = glm::vec3(eye4);
}
