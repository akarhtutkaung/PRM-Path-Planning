#include "Obstacle.h"

Obstacle::Obstacle(std::vector<Vector2 *> *vert) {
  vertices = *vert;

  if (vertices.size() > 1) {
    for (int i = 0; i < vertices.size(); i++) {
      Vector2 *p1 = vertices.at(i);
      Vector2 *p2 = vertices.at((i + 1) % vertices.size());

      double p1x = p1->getX();
      double p2x = p2->getX();
      double p1y = p1->getY();
      double p2y = p2->getY();

      Vector2 *tmp = p1;
      double tmp_x = tmp->getX();
      double tmp_y = tmp->getY();

      do {
        ingombro.push_back(tmp);

        if (p1x == p2x && p1y != p2y) {  // straight vertical
          if (p1y < p2y)
            tmp_y++;
          else if (p1y > p2y)
            tmp_y--;
        } else if (p1x != p2x && p1y == p2y) {  // straight horizontal
          if (p1x < p2x)
            tmp_x++;
          else if (p1x > p2x)
            tmp_x--;
        } else {  // straight obliges
          if (p1x < p2x)
            tmp_x++;
          else if (p1x > p2x)
            tmp_x--;

          tmp_y = ((tmp_x - p1x) / (p2x - p1x)) * (p2y - p1y) + p1y;
        }

        tmp = new Vector2(tmp_x, tmp_y);

      } while (!(tmp->getX() == p2->getX() && tmp->getY() == p2->getY()));
    }
  } else
    ingombro.push_back(vertices.at(0));
}

std::vector<Vector2 *> *Obstacle::getClutter() { return &ingombro; }

double Obstacle::Distance(Vector2 p1, Vector2 p2) {
  return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
              (p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
}


std::vector<Vector2 *> Obstacle::getVertices(){
  return vertices;
}