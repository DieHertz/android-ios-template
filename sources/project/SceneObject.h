//
//  SceneObject.h
//  template
//
//  Created by Alexander Pavlov on 14.12.13.
//  Copyright (c) 2013 SachsHome. All rights reserved.
//

#ifndef template_SceneObject_h
#define template_SceneObject_h

class Shape;
class Mass;

struct SceneObject {
    Shape* shape;
    Mass* mass;
};

#endif
