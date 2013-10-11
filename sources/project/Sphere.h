#ifndef Sphere_h
#define Sphere_h

#include "Shape.h"
#include "Geometry.h"

#include <RenderDevice.h>

#include <vector>

class Sphere : public Shape {
    static const int defaultSubdivs = 5;

public:
    Sphere(const float radius, const int subdivs = defaultSubdivs) : radius(radius), subdivs(subdivs) {
        tessellate();
        fillBuffers();
    }

    virtual ~Sphere() {
        glDeleteBuffers(1, &mTrianglesVbo);
        glDeleteBuffers(1, &mLinesVbo);
    }

    virtual void draw(const bool wireframe) override {
        RenderDevice::translate(x, y, z);
        if (wireframe) {
            RenderDevice::draw(mLinesVbo, mLines.size() * 2, GL_LINES);
        } else {
            RenderDevice::draw(mTrianglesVbo, mTriangles.size() * 3, GL_TRIANGLES);
        }
        RenderDevice::translate(-x, -y, -z);
    }

    float radius;
    int subdivs;

private:
    void tessellate() {
        std::vector<Triangle> triangles;
        triangles.reserve(12);

        const float r = radius / std::sqrt(3.0f);
        triangles.push_back({ { -r, -r, -r }, { r, r, -r }, { r, -r, -r } });
        triangles.push_back({ { -r, -r, -r }, { r, r, -r }, { -r, r, -r } });
        triangles.push_back({ { -r, r, -r }, { r, r, r }, { r, r, -r } });
        triangles.push_back({ { -r, r, -r }, { r, r, r }, { -r, r, r } });
        triangles.push_back({ { r, -r, -r }, { r, r, r }, { r, -r, r } });
        triangles.push_back({ { r, -r, -r }, { r, r, r }, { r, r, -r } });
        triangles.push_back({ { -r, -r, -r }, { r, -r, r }, { -r, -r, r } });
        triangles.push_back({ { -r, -r, -r }, { r, -r, r }, { r, -r, -r } });
        triangles.push_back({ { -r, -r, -r }, { -r, r, r }, { -r, r, -r } });
        triangles.push_back({ { -r, -r, -r }, { -r, r, r }, { -r, -r, r } });
        triangles.push_back({ { -r, -r, r }, { r, r, r }, { -r, r, r } });
        triangles.push_back({ { -r, -r, r }, { r, r, r }, { r, -r, r } });

        for (int i = 0; i < subdivs; ++i) {
            std::vector<Triangle> newTriangles;
            newTriangles.reserve(triangles.size() * 2);

            for (auto& t : triangles) {
                auto mid = (t.a + t.b) / 2;
                mid = mid * length(t.a) / length(mid);
                newTriangles.push_back({ t.a, t.c, mid });
                newTriangles.push_back({ t.b, t.c, mid });
            }

            triangles.swap(newTriangles);
        }

        mTriangles.swap(triangles);

        createWireframe();
    }

    void createWireframe() {
        std::vector<Line> lines;
        lines.reserve(mTriangles.size() * 3);

        for (auto& t : mTriangles) {
            lines.push_back({ t.a, t.b });
            lines.push_back({ t.b, t.c });
            lines.push_back({ t.c, t.a });
        }

        mLines.swap(lines);
    }

    void fillBuffers() {
        glGenBuffers(1, &mTrianglesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mTrianglesVbo);
        glBufferData(GL_ARRAY_BUFFER, mTriangles.size() * sizeof(decltype(mTriangles)::value_type),
                     mTriangles.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &mLinesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mLinesVbo);
        glBufferData(GL_ARRAY_BUFFER, mLines.size() * sizeof(decltype(mLines)::value_type),
                     mLines.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    std::vector<Triangle> mTriangles;
    std::vector<Line> mLines;

    GLuint mTrianglesVbo = 0;
    GLuint mLinesVbo = 0;
};

#endif /* Sphere_h */
