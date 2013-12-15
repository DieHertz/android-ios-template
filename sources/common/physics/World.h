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
    ~World();
    
private:
    void checkMasses(void);
    void bruteForce(void);
    void sweepPrune(void);
    
    std::vector<Mass*> masses;
    Vector3 g;
};



#endif /* defined(__template__World__) */
