/* Created by Simone Tinella, University of Catania*/
/* Modified into English wordings by Akar (Ace) Kaung, University of Minnesota*/

#include <math.h>

#include <vector>

#include "Point.h"

class Obstacle {
 private:
  std::vector<Point *> vertices;
  std::vector<Point *> ingombro;

 public:
  Obstacle(std::vector<Point *> *vert);
  std::vector<Point *> *getClutter();
  static double Distance(Point p1, Point p2);
};

Obstacle::Obstacle(std::vector<Point *> *vert) {
  vertices = *vert;

  if (vertices.size() > 1) {
    for (int i = 0; i < vertices.size(); i++) {
      Point *p1 = vertices.at(i);
      Point *p2 = vertices.at((i + 1) % vertices.size());

      double p1x = p1->getX();
      double p2x = p2->getX();
      double p1y = p1->getY();
      double p2y = p2->getY();

      Point *tmp = p1;
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

        tmp = new Point(tmp_x, tmp_y);

      } while (!(tmp->getX() == p2->getX() && tmp->getY() == p2->getY()));
    }
  } else
    ingombro.push_back(vertices.at(0));
}

std::vector<Point *> *Obstacle::getClutter() { return &ingombro; }

double Obstacle::Distance(Point p1, Point p2) {
  return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
              (p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
}
