#pragma once

#include <fstream>

struct PPM {
    int32_t width = 600;
    int32_t height = 400;
    // just to avoid casting it to float each time it's multiplied by one of the vector's
    // components
    float max_color_value = 260.0f;
    // array of triplets of color values
    glm::vec3 *data = nullptr;
};

class PPManipulator {
public:
    explicit PPManipulator(const char *filename, int32_t width = 600, int32_t height = 400, float max_color_value = 260.0f) noexcept:
            ppm_{width, height, max_color_value},
            handle_{filename, std::ios::out | std::ios::in | std::ios::binary | std::ios::app} {

        if (!handle_) {
            return;
        }

        writeMagic("P3", width, height, max_color_value);
    }

    ~PPManipulator() {
        if (handle_){
            handle_.close();
        }
    }

    void writeBulk(const glm::vec3 *data) {
        //TODO(threadedstream): fill it
    }

    void writeSingle(const glm::vec3& color) {
        handle_ << static_cast<int32_t>(ppm_.max_color_value * color.r) << ' '
               << static_cast<int32_t>(ppm_.max_color_value * color.g) << ' '
               << static_cast<int32_t>(ppm_.max_color_value * color.b)
               << '\n';
    }

    [[nodiscard]] inline std::fstream& handle() noexcept { return handle_; }

private:
    void writeMagic(const char* ppm_version, int32_t width, int32_t height, float max_color_value) {
        handle_ << ppm_version << '\n'
                << width << ' ' << height << '\n'
                << static_cast<int32_t>(max_color_value) << '\n';
    }

private:
    PPM ppm_;
    std::fstream handle_;
};
