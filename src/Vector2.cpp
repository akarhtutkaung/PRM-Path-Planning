#include "Vector2.h"
#include <math.h>

Vector2::Vector2(double x, double y){
  this->x = x;
  this->y = y;
}

Vector2 Vector2::operator+(const Vector2& v){
  return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) {
  return Vector2(this->x - v.x, this->y - v.y);
}

Vector2 Vector2::operator*(float m) {
  return Vector2(m * this->x, m * this->y);
}

Vector2 Vector2::operator/(float m) {
  return Vector2(this->x / m, this->y / m);
}

double Vector2::getX() { return x; }

double Vector2::getY() { return y; }

Vector2 Vector2::normalized(){
  float magnitude = sqrt(x*x + y*y);
  return Vector2(x/magnitude, y/magnitude);
}

float Vector2::distanceTo(Vector2 rhs){
  float dx = rhs.x - x;
  float dy = rhs.y - y;
  return sqrt(dx*dx + dy*dy);
}

Vector2 Vector2::directionTo(Vector2 rhs){
  Vector2 newVec = Vector2(rhs.x - x, rhs.y - y);
  return newVec.normalized();
}