#pragma once

#include <fstream>
#include <filesystem>

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
    explicit PPManipulator(const char *filename, int32_t width = 600, int32_t height = 400,
                           float max_color_value = 260.0f) noexcept:
            ppm_{width, height, max_color_value} {

        if (std::filesystem::exists(filename)) {
            std::filesystem::remove(filename);
        }

        handle_.open(filename, std::ios::out | std::ios::in | std::ios::binary | std::ios::app);
        if (!handle_) {
            return;
        }

        writeMagic("P3", width, height, max_color_value);
    }

    ~PPManipulator() {
        if (handle_) {
            handle_.close();
        }
    }

    void writeBulk(const glm::vec3 *data) {
        //TODO(threadedstream): fill in later
    }

    void writeSingle(const glm::vec3 &color, int64_t samples_per_pixel) {

        const float scale = 1.0f / static_cast<float>(samples_per_pixel);
        const auto r = clamp(std::sqrt(scale * color.r), 0.0f, 0.999f);
        const auto g = clamp(std::sqrt(scale * color.g), 0.0f, 0.999f);
        const auto b = clamp(std::sqrt(scale * color.b), 0.0f, 0.999f);


        handle_ << static_cast<int32_t>(ppm_.max_color_value * r) << ' '
                << static_cast<int32_t>(ppm_.max_color_value * g) << ' '
                << static_cast<int32_t>(ppm_.max_color_value * b)
                << '\n';
    }

    [[nodiscard]] inline std::fstream &handle() noexcept { return handle_; }

private:
    void writeMagic(const char *ppm_version, int32_t width, int32_t height, float max_color_value) {
        handle_ << ppm_version << '\n'
                << width << ' ' << height << '\n'
                << static_cast<int32_t>(max_color_value) << '\n';
    }

private:
    PPM ppm_;
    std::fstream handle_;
};
