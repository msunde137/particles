// Aline Normoyle, 2020
// Convenience header for utilities and common includes 

#pragma once
#include <iostream>
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <limits>
#include <memory>
#include <random>
#include <cmath>

extern std::ostream& operator<<(std::ostream& o, const glm::mat4& m);
extern std::ostream& operator<<(std::ostream& o, const glm::mat3& m);
extern std::ostream& operator<<(std::ostream& o, const glm::vec3& v);
extern std::ostream& operator<<(std::ostream& o, const glm::vec4& v);
extern std::ostream& operator<<(std::ostream& o, const glm::vec2& v);
inline bool operator<(const glm::vec3& a, const glm::vec3& b) { return a.x < b.x || a.y < b.y || a.z < b.z; }
inline bool operator>=(const glm::vec3& a, const glm::vec3& b) { return !(a < b); }
inline bool operator>(const glm::vec3& a, const glm::vec3& b) { return a.x > b.x || a.y > b.y || a.z > b.z; }
inline bool operator<=(const glm::vec3& a, const glm::vec3& b) { return !(a > b); }

namespace glm
{
   using point3 = glm::vec3;
   using color = glm::vec3;
}
const float pi = glm::pi<float>();
const float infinity = std::numeric_limits<float>::infinity();

float random_float();

float random_float(float min, float max);

inline glm::vec3 random_vec3()
{
    float x = random_float();
    float y = random_float();
    float z = random_float();
    return glm::vec3(x, y, z);
}

inline glm::vec3 random_vec3(const glm::vec3& min, const glm::vec3& max)
{
    float x = random_float(min.x, max.x);
    float y = random_float(min.y, max.y);
    float z = random_float(min.z, max.z);
    return glm::vec3(x, y, z);
}

inline glm::vec4 random_vec4()
{
    return glm::vec4(random_vec3(), random_float());
}

inline glm::vec4 random_vec3(const glm::vec4& min, const glm::vec4& max)
{
    return glm::vec4(random_vec3((glm::vec3)min, (glm::vec3)max), random_float(min.w, max.w));
}

inline glm::vec3 random_unit_cube()
{
    return random_vec3(glm::vec3(-.5, -.5, -.5), glm::vec3(.5, .5, .5));
}

//inline glm::vec3 random_unit_cube() 
//{
//   float x = random_float(-0.5,0.5);
//   float y = random_float(-0.5,0.5);
//   float z = random_float(-0.5,0.5);
//   return glm::vec3(x, y, z);
//}

inline glm::vec3 random_unit_square() 
{
   float x = random_float(-0.5,0.5);
   float y = random_float(-0.5,0.5);
   return glm::vec3(x, y, 0);
}


inline glm::vec3 random_unit_sphere() 
{
    glm::mat4 quat = glm::rotate(glm::mat4(1), random_float(0, 2.0f * 3.142f), glm::vec3(1, 0, 0));
    quat = glm::rotate(quat, random_float(0, 2.0f * 3.142f), glm::vec3(0, 1, 0));
    quat = glm::rotate(quat, random_float(0, 2.0f * 3.142f), glm::vec3(0, 0, 1));
    return glm::vec3(quat * glm::vec4(0, 1, 0, 1));
}

inline glm::vec3 random_unit_ball() 
{
    glm::mat4 quat = glm::rotate(glm::mat4(1), random_float(0, 2.0f * 3.142f), glm::vec3(1, 0, 0));
    quat = glm::rotate(quat, random_float(0, 2.0f * 3.142f), glm::vec3(0, 1, 0));
    quat = glm::rotate(quat, random_float(0, 2.0f * 3.142f), glm::vec3(0, 0, 1));
    return glm::vec3(quat * glm::vec4(1, 0, 0, 1)) * random_float(0.0f,1.0f);
}

inline glm::vec3 random_unit_disk()
{
    glm::vec3 p = random_unit_square();
    while (glm::length(p) >= 1.0f)
    {
        p = random_unit_square();
    }
    return p;
}

// Generate random direction in hemisphere around normal
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline glm::vec3 random_hemisphere(const glm::vec3& normal) 
{
   glm::vec3 in_unit_sphere = random_unit_sphere();
   if (glm::dot(in_unit_sphere, normal) > 0.0f) // In the same hemisphere as the normal
   {
       return in_unit_sphere;
   }
   else
   {
       return -in_unit_sphere;
   }
}

// Generate random unit vector
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline glm::vec3 random_unit_vector() 
{
   return glm::normalize(random_unit_sphere());
}

// test for vec3 close to zero (avoid numerical instability)
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline bool near_zero(const glm::vec3& e) 
{
   // Return true if the vector is close to zero in all dimensions.
   const auto s = 1e-8;
   return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

inline bool near_zero(const glm::vec4& e) 
{
   // Return true if the vector is close to zero in all dimensions.
   const auto s = 1e-8;
   return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s) && (fabs(e[3]) < s);
}

inline bool near_zero(const float& e) 
{
   // Return true if the vector is close to zero in all dimensions.
   const auto s = 1e-8;
   return fabs(e) < s;
}

