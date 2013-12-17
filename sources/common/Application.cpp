#include "Application.h"
#include "ui/WidgetManager.h"

#include <memory>

Application::~Application() {
    
}

void Application::_onCreate() {
    onCreate();
}

void Application::_onSurfaceCreated() {
    if (mContextCreated) {
        onContextLost();
    }

    onContextCreated();
    WidgetManager::instance()->onContextCreated();
    mContextCreated = true;
    mTimer.reset();
}

void Application::_onResize(const int width, const int height) {
    onResize(width, height);
    WidgetManager::instance()->onResize(width, height);
}

bool Application::_onBackPressed() {
    return onBackPressed();
}

void Application::_onUpdate() {
    mTimer.update();
    const auto elapsed = mTimer.elapsed();
    onUpdate(elapsed);
    WidgetManager::instance()->onUpdate(elapsed);
}

void Application::_onDraw() {
    onDraw();
    WidgetManager::instance()->onDraw();
}

void Application::_onTouch(TouchEvent event) {
    onTouch(event);
    if (!event.isAccepted()) WidgetManager::instance()->onTouch(event);
}

Application* Application::getInstance() {
    static std::unique_ptr<Application> instance(createApplication());
    return instance.get();
}
