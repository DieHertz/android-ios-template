#ifndef Application_h
#define Application_h

#include "Timer.h"
#include "TouchEvent.h"

class Application;

extern Application* createApplication();

class TouchEvent;

class Application {
protected:
    virtual void onCreate() {}
    virtual void onContextCreated() {}
    virtual void onContextLost() {}
    virtual void onResize(const int width, const int height) {}
    virtual void onUpdate(const float delta) {}
    virtual void onDraw() {}
    virtual void onTouch(TouchEvent& event) {}
    virtual bool onBackPressed() { return false; }

public:
    virtual ~Application() = 0;

    void _onCreate();
    void _onSurfaceCreated();
    void _onResize(const int width, const int height);
    bool _onBackPressed();
    void _onUpdate();
    void _onDraw();
    void _onTouch(TouchEvent event);

    static Application* getInstance();

private:
    bool mContextCreated = false;
    Timer mTimer;
};

#endif /* Application_h */
