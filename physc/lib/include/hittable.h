#pragma once

class Ray;

struct Hittable{
    // arghhhh. Do i need to rename it to something more appropriate? Well, nevermind
    virtual bool intersects(Ray& r, float& t, float t_min, float t_max) = 0;
    virtual ~Hittable() {};
};