//
//  Mass.cpp
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#include "Mass.h"
#include <cmath>

Mass::Mass(float m, float radius, Vector3 r, Vector3 v) {
    this->setM(m);
    this->radius = radius;
    this->r = r;
    this->v = v;
};

void Mass::setM(float m) {
    this->m = m;
    type = MassType::Dynamic;
}

float Mass::getRadius() {
    return radius;
}

void Mass::addForce(Vector3 force) {
    a += force/m;
}

void Mass::addAcceleration(const Vector3 &acc) {
    a += acc;
}

void Mass::resetAcceleration() {
    a = { 0, 0, 0 };
}

void Mass::calculate(float dt) {
    if (this->type != MassType::Static)
        eulerStep(dt);
}

void Mass::eulerStep(float dt) {
    v += a*dt;
    r += v*dt;

    a = { 0, 0, 0 };
}

void Mass::move(Vector3 d) {
    r += d;
}

void Mass::collide(Mass* a, Mass* b) {
    if (a == b)
        return;
    
    float min = a->radius + b->radius;
    if (std::abs(a->r.y - b->r.y) > (min - 1e-3))
        return;
    
    float minSQ = min*min;
    
    Vector3 delta = b->r - a->r;
    Vector3 v = b->v - a->v;
    
    // check move direction
    if (v*delta >= 0.0)
        return;
    
    const float lengthSQ = delta.lengthSQ();
    
    if (lengthSQ < 1e-8)
        return;
    if (lengthSQ > minSQ)
        return;
    
    Vector3 n = delta.n();
    Vector3 d = (n*min - delta)*0.7;

    a->r -= d/2;
    b->r += d/2;

    const float kn = 0.95;
    Vector3 v1 = n*(a->v*n);
    Vector3 v2 = n*(b->v*n);
    
    a->v = a->v - v1 + (v1*(a->m - b->m) + v2*2*b->m)/(a->m + b->m)*kn;
    b->v = b->v - v2 + (v2*(b->m - a->m) + v1*2*a->m)/(a->m + b->m)*kn;
}
