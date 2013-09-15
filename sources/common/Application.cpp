#include "Application.h"

#include <memory>

Application::~Application() {
    
}

void Application::onCreate() {
    
}

void Application::onContextCreated() {
    
}

void Application::onResize(const int width, const int height) {
    
}

void Application::onUpdate() {
    onUpdate(0);
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
