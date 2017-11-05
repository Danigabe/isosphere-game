#ifndef ISOSHPERE_CVECTOR_H
#define ISOSHPERE_CVECTOR_H

#include "Globals.h"

const float PI = 3.14159565;
// multiply to convert degrees in radians
const float DEGTORAD = PI / 180.0;
// multiply to convert radians in degrees
const float RADTODEG = 180.0 / PI;

class cVector {
public:
  cVector() : x(0.0f), y(0.0f), z(0.0f) { }
  cVector(float px, float py, float pz = 0.0f) : x(px), y(py), z(pz) { }

  cVector operator+(const cVector& v2) const;
  cVector& operator+=(const cVector& v2);
  cVector operator-(const cVector& v2) const;
  cVector& operator-=(const cVector& v2);
  cVector operator*(const float p) const;
  cVector& operator*=(const float p);
  cVector operator/(const float p) const;
  cVector& operator/=(const float p);
  cVector operator-() const;
  cVector& operator=(const cVector& v);

  float length() const;
  void normalize();
  static cVector normalize(const cVector& v);

  float dot(const cVector& v2) const;
  static float dot(const cVector& v1, const cVector& v2);

  cVector cross(const cVector& v2) const;
  static cVector cross(const cVector& v1, const cVector& v2);

  friend std::ostream& operator<<(std::ostream& stream, const cVector& v);

  float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const cVector& v);

#endif