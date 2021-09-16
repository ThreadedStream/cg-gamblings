#pragma once

#include "hittable.h"

struct out_of_bound_error : std::runtime_error{
public:
    out_of_bound_error() : std::runtime_error("out-of-bound exceptions has occurred") {};
};

// TODO(threadedstream): create .cpp file/
class Scene{
public:
    Scene(const int64_t capacity = 2) : size_{0}, cap_{capacity} {
        //NOTE(threadedstream): calling "calloc", as hittable does not have a constructor
        hittables_ = reinterpret_cast<Hittable**>(calloc(cap_, sizeof(Hittable)));
        if (!hittables_){
            // TODO(threadedstream): handle a case with "hittables" being nullptr
            // raise an exception?
        }
    }

    // TODO(threadedstream): i'm not confident about proper release of
    // upon destruction of Scene object
    ~Scene() { delete[] hittables_; }

    template<typename ... Args>
    void addObjects(Args&& ... args){
        // TODO(threadedstream): fill in that later
    }

    bool getClosestT(Ray& r, HitRecord& hit_record) {
        float closest_t{0.0f};
        bool has_intersection {false};
        HitRecord temp_rec {};

        for (int64_t idx = 0; idx < size_; idx++) {
            if (hittables_[idx]->intersects(r, closest_t, 1e-6, 1e5, temp_rec)) {
                has_intersection = true;
                hit_record = temp_rec;
            }
        }
        return has_intersection;
    };

    inline void addObject(Hittable* hittable) {
        // TODO(threadedstream): is there a way to avoid branch here?
        if (size_ >= cap_) {
            _initializeNewStorage();
        }

        hittables_[size_++] = hittable;
    }

    inline Hittable* operator[] (int64_t idx){
        if (idx < 0 || idx >= size_) { throw out_of_bound_error(); }
        return hittables_[idx];
    }

    template<int64_t idx>
    inline Hittable* compile_time_get() {
        // it's not compile time due to size_ not being const
        static_assert(idx > 0 && idx < size());
        return hittables_[idx];
    }

    [[nodiscard]] inline Hittable** hittables() noexcept { return hittables_; }
    [[nodiscard]] inline constexpr int64_t size() noexcept { return size_; }
    [[maybe_unused]] [[nodiscard]] inline constexpr int64_t cap() noexcept { return cap_; }

private:
    void _initializeNewStorage() {
        int64_t new_cap = cap_ * 2;
        // TODO(threadedstream): is that a good choice?
        hittables_ = reinterpret_cast<Hittable**>(realloc(hittables_, new_cap));
        cap_ = new_cap;
    }


private:
    // i do need to have pointers, since sizes of child classes are undefined
     Hittable** hittables_;
    int64_t size_;
    int64_t cap_;
};