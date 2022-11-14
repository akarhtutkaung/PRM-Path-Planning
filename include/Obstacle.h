#include <math.h>

#include <vector>

#include "Vector2.h"

class Obstacle {
 private:
  std::vector<Vector2 *> vertices;
  std::vector<Vector2 *> ingombro;

 public:
  Obstacle(std::vector<Vector2 *> *vert);
  std::vector<Vector2 *> *getClutter();
  static double Distance(Vector2 p1, Vector2 p2);
  std::vector<Vector2 *> getVertices();
};