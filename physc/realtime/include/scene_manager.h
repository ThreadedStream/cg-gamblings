#pragma once

#include <iostream>
#include "scene.h"
#include "sample_scene.h"
#include "lighting_scene.h"

class SceneManager final {
public:

    static SceneManager& instance() {
        static SceneManager instance_;
        return instance_;
    }

    template<typename T>
    T* switchUp() {
        if (current_scene_)
            unloadCurrentScene();
        return loadScene<T>();
    }

private:
    template<typename T>
    T* loadScene() {
        static_assert(std::is_base_of_v<Scene, T>, "T is not a child of Scene");
        current_scene_ = new T();
        return reinterpret_cast<T*>(current_scene_);
    }

    void unloadCurrentScene() {
        free(current_scene_);
        current_scene_ = nullptr;
    }

    SceneManager() {}

private:
    Scene* current_scene_;

};
