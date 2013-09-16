#ifndef Template_h
#define Template_h

#include <Application.h>
#include <ShaderProgram.h>

#include <memory>

class Template : public Application {
public:
    Template();

    virtual void onContextCreated() override;
    virtual void onContextLost() override;
    virtual void onResize(const int width, const int height) override;
    virtual void onUpdate(const float delta) override;
    virtual void onDraw() override;
    virtual bool onBackPressed() override;

private:
    std::unique_ptr<ShaderProgram> mProgram;
    float mTime;
};

#endif /* Template_h */
