#ifndef Template_h
#define Template_h

#include "Geometry.h"

#include <Application.h>
#include <ShaderProgram.h>

#include <memory>
#include <vector>

class Template : public Application {
public:
    Template();

    virtual void onContextCreated() override;
    virtual void onContextLost() override;
    virtual void onResize(const int width, const int height) override;
    virtual void onUpdate(const float delta) override;
    virtual void onDraw() override;
    virtual void onTouch(const TouchEvent& event) override;
    virtual bool onBackPressed() override;

private:
    void reset();
    void subdiv();
    void createLine();

    std::unique_ptr<ShaderProgram> mProgram;
    float mTime = 0;

    float mX;
    float mY;

    float mEx = -0.4f;
    float mEy = 0.05f;
    float mEz = -0.2f;

    float mTimer = 0;

    bool wireframe = true;

    std::vector<Triangle> mTriangles;
    std::vector<Line> mLines;
};

#endif /* Template_h */
