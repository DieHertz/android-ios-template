//
//  Mass.cpp
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#include "Mass.h"
#include <math.h>

Mass::Mass(float _m, float _radius, Vector3 _r, Vector3 _v) {
    this->setM(_m);
    radius = _radius;
    links = 0;
    linksMax = 6;
    r = _r;
    v = _v;
    dr = _v;
    dtt = 1;
    rt = Vector3(r - dr);
};

void Mass::setM(float _m) {
    m = _m;
    invM = (m != INFINITY ? 1/m : 0.0);
    type = (m != INFINITY ? MassType::Dynamic : MassType::Static);
}

void Mass::addForce(Vector3 force) {
    a += force/m;
}

void Mass::addAcceleration(const Vector3 &acc) {
    a += acc;
}

void Mass::resetAcceleration() {
    a = {0, 0, 0};
}

void Mass::calculate(float dt) {
    
    if (this->type != MassType::Static)
        eulerStep(dt);
    
    checkWalls(dt);
}

void Mass::eulerStep(float dt) {
    
    v += a*dt;
    r += v*dt;

    a = {0, 0, 0};
}

void Mass::verletStep(float dt) {
    if (this->type == MassType::Static)
        return;

    dr = (r - rt);
    rt = r;
    r += dr*(dt/dtt) + a*(dt*dt);

    a = {0, 0, 0};
}

void Mass::move(Vector3 d) {
    r += d;
}

void Mass::checkWalls(float dt) {
    
//    if (r.y < 0) {
//        v.y = 0;
//        r.y = 0;
//    }
    
    float kn = 0.9;
    float k = 0.95;

    const float d = 3;
    
    float yb = -d;
    if (r.y < yb) {
        v.y = -v.y*kn;
        v *= k;
        r.y = yb;
    }
    
    yb = d;
    if (r.y > yb) {
        v.y = -v.y*kn;
        v *= k;
        r.y = yb;
    }
    
    float xb = -d;
    if (r.x < xb) {
        v.x = -v.x*kn;
        v *= k;
        r.x = xb;
    }
    
    xb = d;
    if (r.x > xb) {
        v.x = -v.x*kn;
        v *= k;
        r.x = xb;
    }
    
    float zb = -d;
    if (r.z < zb) {
        v.z = -v.z*kn;
        v *= k;
        r.z = zb;
    }
    
    zb = d;
    if (r.z > zb) {
        v.z = -v.z*kn;
        v *= k;
        r.z = xb;
    }
    
    v*=0.995;
}

void Mass::collide(Mass *a, Mass *b) {
    
    //    if (a->invM == 0 || b->invM == 0)
    //        return;
    
    if (a == b)
        return;
    
    float min = a->radius + b->radius;
    if (fabsf(a->r.y - b->r.y) > (min - 1e-3))
        return;
    
    float minSQ = min*min;
    
    Vector3 delta = b->r - a->r;
    Vector3 v = b->v - a->v;
    
    // проверка направления движения
    if (v*delta >= 0.0)
        return;
    
    float lengthSQ = delta.lengthSQ();
    
    if (lengthSQ < 1e-8)
        return;
    if (lengthSQ > minSQ)
        return;
    
    Vector3 d;
    Vector3 n = delta.n();
    //не на полную длину, ограничить
    d = (n*min - delta)*0.7;//*1.01;

    a->r -= d/2;
    b->r += d/2;

    float kn = 0.95;
    Vector3 v1 = n*(a->v*n);
    Vector3 v2 = n*(b->v*n);
    
    a->v = a->v - v1 + (v1*(a->m - b->m) + v2*2*b->m)/(a->m + b->m)*kn;
    b->v = b->v - v2 + (v2*(b->m - a->m) + v1*2*a->m)/(a->m + b->m)*kn;
}

Mass::~Mass() {
}
