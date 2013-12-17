//
//  World.h
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#ifndef __template__World__
#define __template__World__

#include <vector>
#include "Vector3.h"

class Mass;

class World {
public:
    World();
    void addMass(Mass* m);
    void step(float dt);
    void setBoundary(Vector3 min, Vector3 max);
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

#endif /* defined(__template__World__) */
