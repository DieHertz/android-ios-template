#ifndef RenderDevice_h
#define RenderDevice_h

class ShaderProgram;

class RenderDevice {
    RenderDevice() = delete;
    RenderDevice(const RenderDevice&) = delete;

public:
    static void clearColor(const float r, const float g, const float b, const float a);
    static void clear();
    static void viewport(const float x, const float y, const float w, const float h);

    static void begin(const ShaderProgram& program);

    static void drawLine(const float* vertices, const float* colors, const int points,
                         const ShaderProgram& program);
};

#endif /* RenderDevice_h */
