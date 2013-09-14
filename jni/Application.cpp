#include "Application.h"
#include "RenderDevice.h"

void Application::onCreate() {

}

void Application::onResize(const int width, const int height) {

}

void Application::onUpdate() {

}

void Application::onDraw() {
    glClearColor(0.63f, 0.35f, 0.54f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::onTouch(const TouchEvent& event) {

}
