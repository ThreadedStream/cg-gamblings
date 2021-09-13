#pragma once

#include "hittable.h"

class Scene{
public:
    Scene(const int64_t capacity = 2) : size_{0}, cap_{capacity} {
        //NOTE(threadedstream): calling "calloc", as hittable does not have a constructor
        hittables_ = reinterpret_cast<Hittable**>(calloc(cap_, sizeof(Hittable)));
        if (!hittables_){
            // TODO(threadedstream): handle a case with "hittables" being nullptr
            // do i raise an exception?
        }
    }

    ~Scene() { delete[] hittables_; }

    void addObject(Hittable* hittable) {
        // TODO(threadedstream): is there a way to avoid branch here?
        if (size_ >= cap_) {
            _initializeNewStorage();
        }

        hittables_[size_++] = hittable;
    }

    void iterateThroughHittables() {
        Ray r(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 10.0f});
        float t;
        for (int32_t i = 0; i < size_; i++) {
            hittables_[i]->intersects(r, t, 0.00001, 100000.0f);
        }
    }


private:
    void _initializeNewStorage() {
        int64_t new_cap = cap_ * 2;
        hittables_ = reinterpret_cast<Hittable**>(realloc(hittables_, new_cap));
        cap_ = new_cap;
    }


private:
    // i do need to have pointers, since sizes of child classes are undefined
     Hittable** hittables_;
    int64_t size_;
    int64_t cap_;
};