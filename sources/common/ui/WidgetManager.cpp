#include "WidgetManager.h"
#include "Widget.h"
#include "TouchEvent.h"

#include <stack>
#include <algorithm>

void WidgetManager::onContextCreated() {
    _painter.reset();
    _painter = std::unique_ptr<Painter>(new Painter);
}

void WidgetManager::onResize(const int width, const int height) {
    _painter->setRootTransform({ 0, 0, width, height });
}

void WidgetManager::onDraw() {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::function<void(Widget*)> draw = [this, &draw] (Widget* widget) {
        widget->onDraw(_painter.get());

        _painter->pushTransform(widget->pos());
        for (auto child : widget->_children) {
            draw(child);
        }
        _painter->popTransform();
    };

    for (auto widget : _topLevelWidgets) {
        draw(widget);
    }

    glDisable(GL_BLEND);
}

void WidgetManager::onUpdate(const float delta) {
    std::stack<Widget*> widgets;

    for (auto topLevelWidget : _topLevelWidgets) {
        widgets.push(topLevelWidget);

        while (!widgets.empty()) {
            auto widget = widgets.top();
            widgets.pop();

            for (auto child : widget->_children) {
                widgets.push(child);
            }

            widget->onUpdate(delta);
        }
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

    if (!widget->parent()) {
        _topLevelWidgets.insert(_topLevelWidgets.end(), widget);
    }
}

void WidgetManager::unregisterWidget(Widget* widget) {
    _widgets.erase(widget);

    if (!widget->parent()) {
        std::remove(_topLevelWidgets.begin(), _topLevelWidgets.end(), widget);
    }
}
