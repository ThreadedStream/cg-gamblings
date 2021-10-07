#pragma once

#include <fstream>
#include <string_view>
#include <filesystem>


namespace fs{
    static char* loadShaderFromFile(const char* path) {
        std::ifstream istream(path, std::ios::app | std::ios::in);
        if (!istream) {
            return nullptr;
        }

        istream.seekg(0, std::ios::end);
        const auto file_size = istream.tellg();
        istream.seekg(0);
        // TODO(threadedstream): is it a callee's responsibility to check for nullity?
        char* contents = static_cast<char*>(calloc(file_size, 1));
        if (!contents) {
            return nullptr;
        }

        istream.read(contents, file_size);
        return contents;
    }
}
