#include "WidgetManager.h"
#include "Widget.h"
#include "TouchEvent.h"

void WidgetManager::onContextCreated() {
    _painter.reset();
    _painter = std::unique_ptr<Painter>(new Painter);
}

void WidgetManager::onResize(const int width, const int height) {
    _painter->clearTransformStack();
    _painter->pushTransform({ 0, 0, width, height });
}

void WidgetManager::onDraw() {
    for (auto widget : _widgets) {
        widget->onDraw(_painter.get());
    }
}

void WidgetManager::onUpdate(const float delta) {
    for (auto widget : _widgets) {
        widget->onUpdate(delta);
    }
}

void WidgetManager::onTouch(TouchEvent& event) {
    for (auto widget : _widgets) {
        if (event.isAccepted()) break;
        widget->onTouch(event);
    }
}

void WidgetManager::registerWidget(Widget* widget) {
    _widgets.insert(widget);
}

void WidgetManager::unregisterWidget(Widget* widget) {
    _widgets.erase(widget);
}
