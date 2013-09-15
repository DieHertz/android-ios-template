#ifndef Template_h
#define Template_h

#include <Application.h>

class Template : public Application {
public:
    virtual void onContextCreated() override;
    virtual void onResize(const int width, const int height) override;
    virtual void onDraw() override;
    virtual bool onBackPressed() override;
};

#endif /* Template_h */
