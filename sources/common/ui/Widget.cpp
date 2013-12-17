#include "Widget.h"
#include "WidgetManager.h"
#include "Painter.h"

Widget::Widget(Widget* parent) : _parent(parent) {
    WidgetManager::instance()->registerWidget(this);
}

Widget::~Widget() {
    WidgetManager::instance()->unregisterWidget(this);
}

void Widget::onDraw(Painter* painter) {
    painter->drawRect(_geometry, { 1, 0, 0, 0 });
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
