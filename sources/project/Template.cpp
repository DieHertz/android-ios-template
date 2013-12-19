#include "Template.h"

#include "Model.h"
#include "Sphere.h"

#include <RenderDevice.h>
#include <Log.h>
#include <TouchEvent.h>

#include <math/Vector4.h>
#include <math/Matrix4.h>
#include <math/MathFunctions.h>
#include <physics/Mass.h>
#include <physics/World.h>

#include <random>

void Template::onCreate() {
    widgetOne.setGeometry({ 0, 0, 150, 100 });
    widgetOne.setColor({ 0.5f, 0.75f, 0.3f, 1 });

    widgetTwo.setGeometry({ 0, 200, 50, 50 });
    widgetTwo.setColor({ 1, 1, 1, 1 });

    widgetThree.setGeometry({ 100, 100, 300, 300 });
    widgetThree.setColor({ 0.1f, 0.55f, 0.75f, 0.6f });

    auto childWidget = new Widget(&widgetThree);
    childWidget->setGeometry({ 50, 50, 200, 200 });
    childWidget->setColor({ 1, 0, 0, 0.3f });

    auto childChildWidget = new Widget(childWidget);
    childChildWidget->setGeometry({ 50, 50, 100, 100 });
    childChildWidget->setColor({ 0, 0.8f, 0.2f, 1 });
}

void Template::onContextCreated() {
    Log::info("%s: %s", __FUNCTION__, glGetString(GL_VERSION));

    const auto vShaderSrc = glsl(
        attribute vec3 aPosition;

        uniform mat4 uModelViewProjection;
        uniform mat4 uModelView;

        varying float depth;

        void main() {
            gl_Position = uModelViewProjection * vec4(aPosition, 1);
            depth = 0.2 * (abs(gl_DepthRange.diff) * gl_Position.w) / gl_Position.z;
        }
    );

    const auto fShaderSrc = glsl(
        precision mediump float;

        varying float depth;

        void main() {
            gl_FragColor = vec4(0.6, 0.2, 0.3, 1) + vec4(depth, depth, depth, 1);
        }
    );

    mProgram = std::unique_ptr<ShaderProgram>(new ShaderProgram(vShaderSrc, fShaderSrc));

    createScene();
}

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
        
        auto shape = new Sphere(mass->getRadius() * scale, 5);
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
    glEnable(GL_DEPTH_TEST);

    RenderDevice::begin(mProgram.get());

    for (auto& shape : mShapes) {
        shape->draw(wireframe);
    }

    RenderDevice::end();
}

void Template::onTouch(TouchEvent& event) {
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
    Vector3 ortho { Math::cross(mEye, mUp).n() };
    Vector4 eye4(mEye, 1.0f);
    Vector4 up4(mUp, 1.0f);
    
    eye4 = eye4 * Math::rotate(Matrix4(), degrees, ortho);
    up4 = up4 * Math::rotate(Matrix4(), degrees, ortho);

    mEye = Vector3(eye4);
    mUp = Vector3(up4);
}

void Template::left(const float degrees) {
    Vector4 eye4 {
        Vector4(mEye, 1.0f) * Math::rotate(Matrix4(), degrees, Vector3(mUp))
    };
    
    mEye = Vector3(eye4);
}
