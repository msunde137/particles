#include <iostream>
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include "AGLM.h"

std::ostream& operator<<(std::ostream& o, const glm::mat4& m)
{
   char line[1024];
   for (int i = 0; i < 4; i++)
   {

      sprintf(line, "%10f, %10f, %10f, %10f",
         m[i][0], m[i][1], m[i][2], m[i][3]);
      o << line;
   }
   return o;
}

std::ostream& operator<<(std::ostream& o, const glm::mat3& m)
{
   char line[1024];
   for (int i = 0; i < 3; i++)
   {

      sprintf(line, "%10f, %10f, %10f",
         m[i][0], m[i][1], m[i][2]);
      o << line;
   }
   return o;
}

std::ostream& operator<<(std::ostream& o, const glm::vec3& v)
{
   char line[1024];
   sprintf(line, "%10f, %10f, %10f", v[0], v[1], v[2]);
   o << line;
   return o;
}

std::ostream& operator<<(std::ostream& o, const glm::vec4& v)
{
   char line[1024];
   sprintf(line, "%10f, %10f, %10f, %10f", v[0], v[1], v[2], v[3]);
   o << line;
   return o;
}

std::ostream& operator<<(std::ostream& o, const glm::vec2& v)
{
   char line[1024];
   sprintf(line, "%10f, %10f", v[0], v[1]);
   o << line;
   return o;
}

static std::random_device rd;
static std::mt19937 generator(rd());
float random_float()
{
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

float random_float(float min, float max)
{
    assert(min < max);
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}