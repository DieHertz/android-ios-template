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
    std::vector<Mass*> masses;
    
    void step(float dt);
    
    void makeFountain(void);
    void fountainAddMass();
    
    ~World();
private:
    void checkMasses(void);
    void bruteForce(void);
    void sweepPrune(void);
    
    Vector3 g;
};



#endif /* defined(__template__World__) */
