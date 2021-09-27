#pragma once

#include <cstdint>

class Scene {
public:
    Scene() = default;

    Scene(const Scene &other) = default;

    Scene &operator=(const Scene &other) = default;

    virtual ~Scene() {};

    virtual void prepareBufferObjects() = 0;

    virtual void prepareTextureData() = 0;

    virtual void setup() {
        prepareBufferObjects();
        prepareTextureData();
    }
    // TODO(threadedstream): consider adding "draw" function

    virtual void destroy() = 0;

protected:
    uint32_t vao_{0};
    uint32_t vbo_{0};
    uint32_t ebo_{0};
};