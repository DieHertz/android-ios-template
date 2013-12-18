#ifndef WidgetManager_h
#define WidgetManager_h

#include "Painter.h"

#include <set>
#include <list>
#include <memory>

class TouchEvent;
class Widget;

class WidgetManager {
private:
    WidgetManager() = default;

public:
    void onContextCreated();
    void onResize(const int width, const int height);

    void onDraw();
    void onUpdate(const float delta);
    void onTouch(TouchEvent& event);

    void registerWidget(Widget* widget);
    void unregisterWidget(Widget* widget);

    static WidgetManager* instance() {
        static WidgetManager instance;
        return &instance;
    }

private:
    std::list<Widget*> _topLevelWidgets;
    std::set<Widget*> _widgets;
    std::unique_ptr<Painter> _painter;
};

#endif /* WidgetManager_h */
