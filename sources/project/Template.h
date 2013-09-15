#ifndef Template_h
#define Template_h

#include <Application.h>

class Template : public Application {
public:
    void onContextCreated();
    void onResize(const int width, const int height);
    void onDraw();
    bool onBackPressed();
};

#endif /* Template_h */
