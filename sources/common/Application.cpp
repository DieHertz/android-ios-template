#include "Application.h"

#include <memory>

Application::Application() : mContextCreated(false) {

}

Application::~Application() {
    
}

void Application::onCreate() {

}

void Application::onSurfaceCreated() {
    if (mContextCreated) {
        onContextLost();
    }

    onContextCreated();
    mContextCreated = true;
    mTimer.reset();
}

void Application::onContextCreated() {
    
}

void Application::onContextLost() {
    
}

void Application::onResize(const int width, const int height) {
    
}

void Application::onUpdate() {
    mTimer.update();
    onUpdate(mTimer.elapsed());
}

void Application::onUpdate(const float delta) {
    
}

void Application::onDraw() {
    
}

void Application::onTouch(const TouchEvent& event) {
    
}


bool Application::onBackPressed() {
    return false;
}

Application* Application::getInstance() {
    static std::unique_ptr<Application> instance(createApplication());
    return instance.get();
}
