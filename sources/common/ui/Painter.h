#ifndef Painter_h
#define Painter_h

#include "Rect.h"
#include "Color.h"
#include "Point.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>

#include <stack>

class Painter {
public:
    Painter();

    void drawRect(const Rect& r, const Color& c);

    void setRootTransform(const Rect& r);
    void clearTransformStack();
    void pushTransform(const Point& p);
    void popTransform();

private:
    ShaderProgram _shader;
    std::stack<glm::mat4> _transformStack;
};

#endif /* Painter_h */
