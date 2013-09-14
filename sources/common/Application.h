#ifndef Application_h
#define Application_h

#include "TouchEvent.h"

class Application {
public:
    void onCreate();
    void onContextCreated();
    void onResize(const int width, const int height);
    void onUpdate();
    void onDraw();
    void onTouch(const TouchEvent& event);

    bool onBackPressed();
};

#endif /* Application_h */
