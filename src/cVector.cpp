#include "cVector.h"
#include <math.h>

cVector cVector::operator+(const cVector& v2) const {
  return cVector(x + v2.x, y + v2.y, z + v2.z);
}

cVector& cVector::operator+=(const cVector& v2) {
  x += v2.x;
  y += v2.y;
  z += v2.z;
  return *this;
}

cVector cVector::operator-(const cVector& v2) const {
  return cVector(x - v2.x, y - v2.y, z - v2.z);
}

cVector& cVector::operator-=(const cVector& v2) {
  x -= v2.x;
  y -= v2.y;
  z -= v2.z;
  return *this;
}

cVector cVector::operator*(const float p) const {
  return cVector(x*p, y*p, z*p);
}

cVector& cVector::operator*=(const float p) {
  x *= p;
  y *= p;
  z *= p;
  return *this;
}

cVector cVector::operator/(const float p) const {
  return cVector(x/p, y/p, z/p);
}

cVector& cVector::operator/=(const float p) {
  x /= p;
  y /= p;
  z /= p;
  return *this;
}

cVector cVector::operator-() const {
  return cVector(-x, -y, -z);
}

cVector& cVector::operator=(const cVector& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

float cVector::length() const {
  float x2 = x*x;
  float y2 = y*y;
  float z2 = z*z;
  return sqrt(x2+y2+z2);
}

void cVector::normalize() {
  float vlength = length();
  if (vlength == 0.0f)
    return;
  x /= vlength;
  y /= vlength;
  z /= vlength;
}

cVector cVector::normalize(const cVector& v) {
  float vlength = v.length();
  if (vlength == 0.0f)
    return cVector();

  cVector retv;
  retv.x = v.x / vlength;
  retv.y = v.y / vlength;
  retv.z = v.z / vlength;
  return retv;
}

float cVector::dot(const cVector& v2) const {
  return cVector::dot(*this, v2);
}

float cVector::dot(const cVector& v1, const cVector& v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector cVector::cross(const cVector& v2) const {
  return cVector::cross(*this, v2);
}

cVector cVector::cross(const cVector& v1, const cVector& v2) {
  cVector v;
  v.x = v1.y*v2.z - v2.y*v1.z;
  v.y = v2.x*v1.z - v1.x*v2.z;
  v.z = v1.x*v2.y - v2.x*v1.y;
  return v;
}

std::ostream& operator<<(std::ostream& stream, const cVector& v) {
  stream << v.x << " " << v.y << " " << v.z;
  return stream;
}