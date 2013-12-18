#ifndef Widget_h
#define Widget_h

#include "Rect.h"
#include "Point.h"
#include "Size.h"
#include "Color.h"

#include <list>

class Painter;
class TouchEvent;

class Widget {
    friend class WidgetManager;

public:
    Widget(Widget* parent = nullptr);
    virtual ~Widget();

    virtual void onDraw(Painter* painter);
    virtual void onUpdate(const float delta);
    virtual void onTouch(TouchEvent& event);

    Widget* parent() { return _parent; }
    Point pos() const { return { _geometry.x, _geometry.y }; }
    Rect geometry() const { return _geometry; }
    Color color() const { return _color; }

    std::list<Widget*> children() const { return _children; }

    void move(const Point& to);
    void resize(const Size& size);
    void setGeometry(const Rect& geometry);
    void setColor(const Color& color);

protected:
    Widget* _parent;

    Rect _geometry;
    Color _color;

    std::list<Widget*> _children;
};

#endif /* Widget_h */
