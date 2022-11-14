#ifndef Vector2_H_
#define Vector2_H_

class Vector2 {
 public:
  double x, y;

 public:
  Vector2(double x, double y);
  Vector2 operator+(const Vector2& v);
  Vector2 operator-(const Vector2& v);
  Vector2 operator*(float m);
  Vector2 operator/(float m);
  Vector2 directionTo(Vector2 rhs);
  Vector2 normalized();
  float distanceTo(Vector2 rhs);
  double getX();
  double getY();
};

#endif  // Vector2_H_