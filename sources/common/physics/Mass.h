#ifndef __template__Mass__
#define __template__Mass__

#include  "math/Vector3.h"

enum class MassType {
    Dynamic,
    Static,
};

class Mass {
public:
    Mass() : Mass(1.0f, 0.08f, Vector3(), Vector3()) {}
    Mass(float m, float radius, Vector3 r, Vector3 v);
    
    void setM(float m);
    float getRadius();
    
    void addForce(Vector3 force);
    void addAcceleration(const Vector3& acc);
    void resetAcceleration();
    
    void calculate(float dt);
    
    static void collide(Mass* a, Mass* b);
    static bool comparePtr(Mass* a, Mass* b) { return a->r.x < b->r.x; }
    
    Vector3 r;
    Vector3 v;
    
private:
    void verletStep(float dt);
    void eulerStep(float dt);
    void move(Vector3 d);
    
    MassType type;
    float m;
    float radius;
    Vector3 a;
    Vector3 f;
};

#endif /* __template__Mass__ */
