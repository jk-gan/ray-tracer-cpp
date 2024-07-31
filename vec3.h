//
// Created by Jun Kai Gan on 27/07/2024.
//

#pragma once

class vec3 {
public:
    double e[3];

    vec3()
        : e { 0, 0, 0 } { }
    vec3(const double x, const double y, const double z)
        : e { x, y, z } { }

    [[nodiscard]] auto x() const -> double { return e[0]; }
    [[nodiscard]] auto y() const -> double { return e[1]; }
    [[nodiscard]] auto z() const -> double { return e[2]; }

    auto operator-() const -> vec3 { return vec3 { -e[0], -e[1], -e[2] }; }
    auto operator[](int i) const -> double { return e[i]; }
    auto operator[](int i) -> double& { return e[i]; }

    auto operator+=(const vec3& v) -> vec3& {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    auto operator*=(double t) -> vec3& {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    auto operator/=(double t) -> vec3& { return *this *= 1 / t; }

    [[nodiscard]] auto length() const -> double { return std::sqrt(length_squared()); }
    [[nodiscard]] auto length_squared() const -> double { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    static auto random() -> vec3 { return { random_double(), random_double(), random_double() }; }
    static auto random(double min, double max) -> vec3 {
        return { random_double(min, max), random_double(min, max), random_double(min, max) };
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;
// Vector Utility Functions

inline auto operator<<(std::ostream& out, const vec3& v) -> std::ostream& {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
inline auto operator+(const vec3& u, const vec3& v) -> vec3 {
    return { u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2] };
}
inline auto operator-(const vec3& u, const vec3& v) -> vec3 {
    return { u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2] };
}
inline auto operator*(const vec3& u, const vec3& v) -> vec3 {
    return { u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2] };
}
inline auto operator*(double t, const vec3& v) -> vec3 { return { t * v.e[0], t * v.e[1], t * v.e[2] }; }
inline auto operator*(const vec3& v, double t) -> vec3 { return t * v; }
inline auto operator/(const vec3& v, double t) -> vec3 { return (1 / t) * v; }

inline auto dot(const vec3& u, const vec3& v) -> double { return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; }

inline auto cross(const vec3& u, const vec3& v) -> vec3 {
    return { u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0] };
}

inline auto unit_vector(const vec3& v) -> vec3 { return v / v.length(); }

inline auto random_in_unit_sphere() -> vec3 {
    while (true) {
        auto p = vec3::random(-1.0, 1.0);
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

inline auto random_unit_vector() -> vec3 { return unit_vector(random_in_unit_sphere()); }

inline auto random_on_hemisphere(const vec3& normal) -> vec3 {
    vec3 on_unit_sphere = random_unit_vector();
    // if the dot product is > 0.0, mean it is in the same hemisphere as the normal
    return dot(on_unit_sphere, normal) > 0.0 ? on_unit_sphere : -on_unit_sphere;
}
