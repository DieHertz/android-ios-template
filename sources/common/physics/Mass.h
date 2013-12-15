//
//  Mass.h
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#ifndef __template__Mass__
#define __template__Mass__

#include "Vector3.h"

enum class MassType {
    Dynamic,
    Static,
};

class Mass {
    
public:
    int mid;
    MassType type;
    int links;
    int linksMax;
    float m;
    float invM;
    float radius;
    Vector3 rt;
    Vector3 r;
    Vector3 dr;
    Vector3 drt;
    Vector3 vt;
    Vector3 v;
    Vector3 at;
    Vector3 a;
    Vector3 f;
    float dtt;
    
    void* data;
    
    Mass() : Mass(1.0f, 0.08f, Vector3(), Vector3()) {}
    Mass(float _m, float _radius, Vector3 _r, Vector3 _v);

    void setM(float _m);
    void addForce(Vector3 force);
    void addAcceleration(const Vector3& acc);
    void resetAcceleration();
    
    void verletStep(float dt);
    void eulerStep(float dt);
    void move(Vector3 d);
    void checkWalls(float dt);
    
    void calculate(float dt);
    void calcVerlet(float dt);
    
    static void collide(Mass* a, Mass* b);
    
    static bool comparePtr(Mass* a, Mass* b) { return a->r.x < b->r.x; }
};

#endif /* defined(__template__Mass__) */
