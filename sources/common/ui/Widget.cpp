#include "Widget.h"
#include "WidgetManager.h"
#include "Painter.h"

#include <algorithm>

Widget::Widget(Widget* parent) : _parent(parent) {
    WidgetManager::instance()->registerWidget(this);

    if (parent) {
        parent->_children.push_back(this);
    }
}

Widget::~Widget() {
    for (auto it = _children.begin(); it != _children.end(); ) {
        delete *it++;
    }

    if (_parent) {
        std::remove(_parent->_children.begin(), _parent->_children.end(), this);
    }

    WidgetManager::instance()->unregisterWidget(this);
}

void Widget::onDraw(Painter* painter) {
    painter->drawRect(_geometry, _color);
}

void Widget::onUpdate(const float delta) {

}

void Widget::onTouch(TouchEvent& event) {

}

void Widget::move(const Point& to) {
    _geometry.x = to.x;
    _geometry.y = to.y;
}

void Widget::resize(const Size& size) {
    _geometry.w = size.w;
    _geometry.h = size.h;
}

void Widget::setGeometry(const Rect& geometry) {
    _geometry = geometry;
}

void Widget::setColor(const Color& color) {
    _color = color;
}
