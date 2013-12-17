//
//  World.cpp
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#include "World.h"
#include "Mass.h"
#include "math/Vector3.h"
#include "math/MathFunctions.h"

#include <algorithm>

World::World() {
    g = { 0, -9.80f, 0 };
    boundaryMin = { -2, -2, -5 };
    boundaryMax = {  2,  2,  5 };
}

void World::addMass(Mass* m) {
    masses.push_back(m);
}

void World::setBoundary(const Vector3 &min, const Vector3 &max) {
    boundaryMin = min;
    boundaryMax = max;
}

void World::checkBoundaryForMass(Mass* mass) {
    const float dampingNormal = 0.9;
    const float damping = 0.95;
    
    struct {
        float min;
        float max;
        float& target;
        float& additional;
    } constraints[] {
        { boundaryMin.x, boundaryMax.x, mass->r.x, mass->v.x },
        { boundaryMin.y, boundaryMax.y, mass->r.y, mass->v.y },
        { boundaryMin.z, boundaryMax.z, mass->r.z, mass->v.z },
    };
    
    for (auto& c : constraints) {
        if (c.target < c.min || c.target > c.max) {
            c.additional *= -dampingNormal;
            mass->v *= damping;
            c.target = Math::clamp(c.target, c.min, c.max);
        }
    }
}

void World::bruteForce() {
    for (int i = 0; i < masses.size() - 1; ++i)
        for (int j = i + 1; j < masses.size(); ++j)
            Mass::collide(masses[i], masses[j]);
}

void World::sweepPrune() {
    const float radius = 0.5f;
    const float minDist = radius * 2;
    
    std::sort(masses.begin() + 1, masses.end(), Mass::comparePtr);
    for (int i = 0; i < masses.size() - 1; ++i)
        for (int j = i + 1; j < masses.size() && masses[i]->r.x + 2*minDist > masses[j]->r.x; ++j)
            Mass::collide(masses[i], masses[j]);
}

void World::step(float dt) {
    dt = 1.0f / 60;
    // add gravity
    for (auto mass : masses) {
        mass->addAcceleration(g);
    }

    // calc
    for (auto mass : masses) {
        mass->calculate(dt);
        checkBoundaryForMass(mass);
    }
    
    for (int j = 0; j < 3; ++j) {
        bruteForce();
        //sweepPrune();
    }
}

World::~World() {
    for (auto mass : masses) {
        delete mass;
    }
}
