#pragma once

#include <iostream>

namespace math {

class vec3 {
public:
  // Methods
  vec3();
  vec3(const float &x, const float &y, const float &z);

  vec3 &add(const vec3 &other);
  vec3 &subtract(const vec3 &other);
  vec3 &multiply(const vec3 &other);
  vec3 &divide(const vec3 &other);

  friend vec3 operator+(vec3 left, const vec3 &right);
  friend vec3 operator-(vec3 left, const vec3 &right);
  friend vec3 operator*(vec3 left, const vec3 &right);
  friend vec3 operator/(vec3 left, const vec3 &right);

  bool operator==(const vec3 &other);
  bool operator!=(const vec3 &other);

  vec3 &operator+=(const vec3 &other);
  vec3 &operator-=(const vec3 &other);
  vec3 &operator*=(const vec3 &other);
  vec3 &operator/=(const vec3 &other);

  friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);

public:
  // Variables
  float x, y, z;
};

} // namespace math
