#ifndef __template__World__
#define __template__World__

#include "math/Vector3.h"
#include <vector>

class Mass;

class World {
public:
    World();
    void addMass(Mass* m);
    void step(float dt);
    void setBoundary(const Vector3& min, const Vector3& max);
    ~World();
    
private:
    void checkMasses();
    void bruteForce();
    void sweepPrune();
    void checkBoundaryForMass(Mass* m);
    
    std::vector<Mass*> masses;
    Vector3 g;
    Vector3 boundaryMin;
    Vector3 boundaryMax;
};

#endif /* __template__World__ */
