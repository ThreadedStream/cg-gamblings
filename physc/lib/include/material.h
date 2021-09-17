#pragma once

struct HitRecord;
class Ray;

class Material {
public:
    virtual bool scatter(Ray& incoming_ray, const HitRecord& hit_record, Color& attenuation, Ray& scattered) noexcept = 0;

    virtual ~Material() {};
};

class Lambertian: public Material {
public:
    [[maybe_unused]] Lambertian(const Color& albedo) : albedo_{albedo} {};

    virtual bool scatter(Ray& incoming_ray,
                         const HitRecord& hit_record,
                         Color& attenuation,
                         Ray& scattered) noexcept override{

        auto scatter_direction = hit_record.normal + random_unit_vector();
        if (vector_near_zero(scatter_direction, 1e-8))
            scatter_direction = hit_record.normal;

        scattered = Ray(hit_record.intersection_point, scatter_direction);
        attenuation = albedo_;
        return true;
    }

    [[maybe_unused]] [[nodiscard]] inline Color& albedo() noexcept { return albedo_; }

private:
    Color albedo_;
};

class Metal : public Material{
public:
    [[maybe_unused]] Metal(const Color& albedo) : albedo_{albedo} {};

    virtual bool scatter(Ray& incoming_ray,
                         const HitRecord& hit_record,
                         Color& attenuation,
                         Ray& scattered) noexcept override {

        const glm::vec3 reflect_vec = reflected(incoming_ray.direction(), hit_record.normal);
        scattered = Ray(hit_record.intersection_point, reflect_vec);
        attenuation = albedo_;
        return glm::dot(scattered.direction(), hit_record.normal) > 0;
    }


    // TODO(threadedstream): gain an intuition on why this formula works
    glm::vec3 reflected(glm::vec3& v, const glm::vec3& normal) {
        return v - 2 * glm::dot(v, normal) * normal;
    }

    [[maybe_unused]] [[nodiscard]] inline Color& albedo() noexcept { return albedo_; }


private:
    Color albedo_;
};
