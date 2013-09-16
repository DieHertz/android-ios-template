#ifndef Application_h
#define Application_h

#include "Timer.h"

class Application;

extern Application* createApplication();

class TouchEvent;

class Application {
protected:
    virtual void onUpdate(const float delta);
    virtual void onContextCreated();
    virtual void onContextLost();

public:
    Application();
    virtual ~Application() = 0;
    
    virtual void onCreate();
    void onSurfaceCreated();
    virtual void onResize(const int width, const int height);
    void onUpdate();
    virtual void onDraw();
    virtual void onTouch(const TouchEvent& event);

    virtual bool onBackPressed();

    static Application* getInstance();

private:
    bool mContextCreated;
    Timer mTimer;
};

#endif /* Application_h */
