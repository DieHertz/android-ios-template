#ifndef Template_h
#define Template_h

#include "Geometry.h"
#include "SceneObject.h"
#include "Shape.h"
#include "physics/World.h"

#include <Application.h>
#include <ShaderProgram.h>
#include <ui/Widget.h>

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <vector>

class Template : public Application {
public:
    virtual void onCreate() override;
    virtual void onContextCreated() override;
    virtual void onContextLost() override;
    virtual void onResize(const int width, const int height) override;
    virtual void onUpdate(const float delta) override;
    virtual void onDraw() override;
    virtual void onTouch(TouchEvent& event) override;

private:
    void up(const float degrees);
    void left(const float degrees);
    
    void createScene();

    std::unique_ptr<ShaderProgram> mProgram;
    float mTime = 0;

    float mX;
    float mY;

    glm::vec3 mEye = glm::vec3(0, 0, 0.5f);
    glm::vec3 mUp = glm::vec3(0, 1.0f, 0);

    float mTimer = 0;

    bool wireframe = true;

    std::vector<std::unique_ptr<Shape>> mShapes;
    std::vector<SceneObject> mObjects;
    
    std::unique_ptr<World> mWorld;

    Widget widgetOne;
    Widget widgetTwo;
    Widget widgetThree;

    static constexpr float scale = 0.05f;
};

#endif /* Template_h */
