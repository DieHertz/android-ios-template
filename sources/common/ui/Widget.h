#ifndef Widget_h
#define Widget_h

#include "Rect.h"
#include "Point.h"
#include "Size.h"

class Painter;
class TouchEvent;

class Widget {
public:
    Widget(Widget* parent = nullptr);
    virtual ~Widget();

    virtual void onDraw(Painter* painter);
    virtual void onUpdate(const float delta);
    virtual void onTouch(TouchEvent& event);

    Widget* parent() { return _parent; }
    Rect geometry() const { return _geometry; }

    [[deprecated]] void move(const Point& to);
    [[deprecated]] void resize(const Size& size);
    [[deprecated]] void setGeometry(const Rect& geometry);

protected:
    Widget* _parent;

    Rect _geometry;
};

#endif /* Widget_h */
