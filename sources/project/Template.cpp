#include "Template.h"

#include "Model.h"
#include "Sphere.h"

#include <RenderDevice.h>
#include <Log.h>
#include <TouchEvent.h>
#include <physics/Mass.h>
#include <physics/World.h>

#include <chrono>
#include <random>

Template::Template() {
}

void Template::onContextCreated() {
    Log::info("%s: %s", __FUNCTION__, glGetString(GL_VERSION));

    const char* vShaderSrc {
        "#version 100\n"

        "attribute vec3 aPosition;"

        "uniform mat4 uModelViewProjection;"
        "uniform mat4 uModelView;"

        "varying float depth;"

        "void main() {"
            "gl_Position = uModelViewProjection * vec4(aPosition, 1);"
            "depth = 0.2 * (abs(gl_DepthRange.diff) * gl_Position.w) / gl_Position.z;"
        "}"
    };

    const char* fShaderSrc {
        "#version 100\n"

        "precision mediump float;"

        "varying float depth;"

        "void main() {"
            "gl_FragColor = vec4(0.6, 0.2, 0.3, 1) + vec4(depth, depth, depth, 1);"
        "}"
    };

    mProgram = std::unique_ptr<ShaderProgram>(new ShaderProgram(vShaderSrc, fShaderSrc));

    RenderDevice::clearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    createScene();
}

const float scale = 0.05;

void Template::createScene() {
    mWorld = std::unique_ptr<World>(new World);
    
    const int objectsCount = 20;
    const float radius = 0.5f;

    auto rnd = [] (const float from, const float to) {
        std::random_device device;
        std::uniform_real_distribution<float> distr(from, to);
        return distr(device);
    };

    for (int i = 0; i < objectsCount; ++i) {
        Vector3 randomPos = { rnd(-2, 2), rnd(-2, 2), rnd(-2, 2) };
        
        auto mass = new Mass(1, radius, randomPos, { 0, 0, 0 });
        mWorld->addMass(mass);
        
        auto shape = new Sphere(mass->radius * scale, 5);
        mShapes.push_back(std::unique_ptr<Shape>(shape));
        
        mObjects.push_back({ shape, mass });
    }
}

void Template::onContextLost() {
    mProgram.reset();

    mShapes.clear();
    mObjects.clear();
}

void Template::onResize(const int width, const int height) {
    RenderDevice::viewport(0, 0, width, height);
    RenderDevice::lookAt(mEye.x, mEye.y, mEye.z,
                         0, 0, 0,
                         mUp.x, mUp.y, mUp.z);
    RenderDevice::perspective(60, static_cast<float>(width) / height, 0.1f, 5.0f);
}

void Template::onUpdate(const float delta) {
    mTime += delta;

    if (mTimer > 0) {
        mTimer -= delta;
    }
    
    mWorld->step(delta);
    
    for (auto& object : mObjects) {
        object.shape->x = object.mass->r.x * scale;
        object.shape->y = object.mass->r.y * scale;
        object.shape->z = object.mass->r.z * scale;
    }
}

void Template::onDraw() {
    RenderDevice::clear();

    RenderDevice::begin(mProgram.get());

    for (auto& shape : mShapes) {
        shape->draw(wireframe);
    }

    RenderDevice::end();
}

void Template::onTouch(const TouchEvent& event) {
    if (event.getType() == TouchEvent::Down) {
        mX = event.getX();
        mY = event.getY();

        if (mTimer > 0) {
            wireframe = !wireframe;
            mTimer = 0;
            return;
        }

        mTimer = 0.2f;
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
