#pragma once

class Ray;
class Material;

struct HitRecord{
    glm::vec3 normal;
    glm::vec3 intersection_point;
    float t;
    std::shared_ptr<Material> material;


    bool front_face;

    inline void set_face_normal(const glm::vec3& ray_direction, const glm::vec3& outward_normal) {
        front_face = glm::dot(ray_direction, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

struct Hittable{
    // arghhhh. Do i need to rename it to something more appropriate? Well, nevermind
    virtual bool intersects(Ray& r, float& t, float t_min, float t_max, HitRecord& hit_record) = 0;
    virtual ~Hittable() {};
};