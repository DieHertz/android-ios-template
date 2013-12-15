#ifndef Template_h
#define Template_h

#include "Geometry.h"

#include <Application.h>
#include <ShaderProgram.h>

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <vector>
#include "SceneObject.h"

#include "Shape.h"

class World;
class Mass;

class Template : public Application {
public:
    Template();

    virtual void onContextCreated() override;
    virtual void onContextLost() override;
    virtual void onResize(const int width, const int height) override;
    virtual void onUpdate(const float delta) override;
    virtual void onDraw() override;
    virtual void onTouch(const TouchEvent& event) override;

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

    std::vector<Shape*> mShapes;
    std::vector<SceneObject> mObjects;
    World* world;
};

#endif /* Template_h */
