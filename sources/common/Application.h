#ifndef Application_h
#define Application_h

class Application;

extern Application* createApplication();

class TouchEvent;

class Application {
public:
    virtual ~Application();

    virtual void onCreate();
    virtual void onContextCreated();
    virtual void onResize(const int width, const int height);
    void onUpdate();
    virtual void onUpdate(const float delta);
    virtual void onDraw();
    virtual void onTouch(const TouchEvent& event);

    virtual bool onBackPressed();

    static Application* getInstance();
};

#endif /* Application_h */
