#ifndef Shape_h
#define Shape_h

class Shape {
public:
    virtual ~Shape() {}

    virtual void draw(const bool wireframe) = 0;

    float x = 0;
    float y = 0;
    float z = 0;
};

#endif /* Shape_h */
