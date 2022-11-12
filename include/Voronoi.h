/* Created by Simone Tinella, University of Catania*/
/* Modified into English wordings by Akar (Ace) Kaung, University of Minnesota*/

#include <math.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "Obstacle.h"

const double unit = 1;
const double search_radius =
    5 * unit * sqrt(2);  // radius searches for neighbors
const double dist_tolerance = unit * sqrt(2);

const double Distance = 5 * unit;  //*sqrt(2); //filter
const int gap = 1;                 // filter

class Voronoi {
 private:
  double length;
  double width;
  std::vector<Obstacle *> obstacles;
  std::vector<Point *> voronoi_points;
  std::vector<Point *> junctions;
  void CreateVoronoi();
  std::vector<Point *> getVoronoiPath(Point departure, Point arrival,
                                      std::vector<Point *> *junctions_s);
  std::vector<Point *> getVoronoiPath2(Point departure, Point arrival);

 public:
  Voronoi(double width, double length, std::vector<Obstacle *> obstacles);
  std::vector<Obstacle *> *getobstacles();
  std::vector<Point *> *getVoronoiPoints();
  std::vector<Point> getPaths(Point departure, Point arrival);
  Point getPointDistanceMinimum(Point p);
  std::vector<Point *> *getJunctions();
};

Voronoi::Voronoi(double width, double length,
                 std::vector<Obstacle *> obstacles) {
  this->obstacles = obstacles;

  // Use this if you don't want the links of the environment explanations
  std::vector<Point *> environment;
  environment.push_back(new Point(0, 0));
  environment.push_back(new Point(width - 1, 0));
  environment.push_back(new Point(width - 1, length - 1));
  environment.push_back(new Point(0, length - 1));
  this->obstacles.push_back(new Obstacle(&environment));

  // use this if you want the edges of the environment
  /*std::vector<Point*> environment;
  environment.push_back(new Point(0,0));
  environment.push_back(new Point(width-1,0));
  this->obstacles.push_back(new Obstacle(&environment));
  std::vector<Point*> environment2;
  environment2.push_back(new Point(width-1,1));
  environment2.push_back(new Point(width-1,length-1));
  this->obstacles.push_back(new Obstacle(&environment2));
  std::vector<Point*> environment3;
  environment3.push_back(new Point(width-2,length-1));
  environment3.push_back(new Point(0,length-1));
  this->obstacles.push_back(new Obstacle(&environment3));
  std::vector<Point*> environment4;
  environment4.push_back(new Point(0,length-2));
  environment4.push_back(new Point(0,1));
  this->obstacles.push_back(new Obstacle(&environment4));*/

  this->length = length;
  this->width = width;

  std::cout << "[!] Creating voronoi points..." << std::endl;
  CreateVoronoi();
  std::cout << "[+] Voronoi map created." << std::endl;
}

std::vector<Obstacle *> *Voronoi::getobstacles() { return &obstacles; }

std::vector<Point *> *Voronoi::getVoronoiPoints() { return &voronoi_points; }

std::vector<Point *> *Voronoi::getJunctions() { return &junctions; }

void Voronoi::CreateVoronoi() {
  for (double tmpY = unit; tmpY < length - unit; tmpY += unit) {
    float percentage = ((float)tmpY / (float)(length - unit)) * 100;
    std::cout << "[!] Processing: " << percentage << "% \r";

    for (double tmpX = unit; tmpX < width - unit; tmpX += unit) {
      Point *tmp_Point = new Point(tmpX, tmpY);

      std::vector<double> distances;
      for (int i = 0; i < obstacles.size(); i++) {
        double minDist = std::numeric_limits<double>::infinity();
        for (int j = 0; j < obstacles.at(i)->getClutter()->size(); j++) {
          double tmp_dist = Obstacle::Distance(
              *tmp_Point, *obstacles.at(i)->getClutter()->at(j));
          if (tmp_dist < minDist) minDist = tmp_dist;
        }
        distances.push_back(minDist);
      }

      // Distance from obstacle's neighbor
      std::sort(distances.begin(), distances.begin() + distances.size());

      double min1 = distances.at(0);
      double min2 = distances.at(1);

      if (fabs(min2 - min1) <= dist_tolerance) {
        voronoi_points.push_back(tmp_Point);

        if (obstacles.size() > 2) {
          double min3 = distances.at(2);
          if (fabs(min2 - min3) <= dist_tolerance &&
              fabs(min3 - min1) <= dist_tolerance)
            junctions.push_back(tmp_Point);
        }

      } else
        delete tmp_Point;
    }
  }
}

std::vector<Point> Voronoi::getPaths(Point departure, Point arrival) {
  std::cout << "[!] Calculating path..." << std::endl;

  std::vector<Point> paths;
  paths.push_back(departure);  // temporary
  double dist = std::numeric_limits<double>::infinity();
  double dist2 = std::numeric_limits<double>::infinity();
  Point *minimum_arrival = NULL;
  Point *minimum = NULL;

  for (int i = 0; i < voronoi_points.size(); i++) {
    Point *p = voronoi_points.at(i);
    double val =
        sqrt((departure.getX() - p->getX()) * (departure.getX() - p->getX()) +
             (departure.getY() - p->getY()) * (departure.getY() - p->getY()));
    double val2 =
        sqrt((arrival.getX() - p->getX()) * (arrival.getX() - p->getX()) +
             (arrival.getY() - p->getY()) * (arrival.getY() - p->getY()));
    if (val < dist) {
      minimum = p;
      dist = val;
    }
    if (val2 < dist2) {
      minimum_arrival = p;
      dist2 = val2;
    }
  }

  if (minimum == NULL) return paths;
  if (minimum_arrival == NULL) return paths;

  paths.push_back(*minimum);

  if (minimum->getX() == arrival.getX() && minimum->getY() == arrival.getY())
    return paths;

  std::vector<Point *> voronoi_path =
      getVoronoiPath(*minimum, *minimum_arrival, NULL);

  if (voronoi_path.size() > 0) {
    Point *tmp = voronoi_path.at(0);
    paths.push_back(*tmp);
    for (int i = 1; i < voronoi_path.size(); i++) {
      if (Obstacle::Distance(*tmp, *voronoi_path.at(i)) >= Distance) {
        paths.push_back(*voronoi_path.at(i));
        tmp = voronoi_path.at(i);
      }
    }

    std::vector<Point> temp;
    for (int i = 0; i < paths.size(); i += gap) {
      temp.push_back(paths.at(i));
    }
    paths = temp;
  }

  paths.push_back(*minimum_arrival);
  paths.push_back(arrival);

  std::cout << "[+] Path generated." << std::endl;
  return paths;
}

std::vector<Point *> Voronoi::getVoronoiPath(
    Point departure, Point arrival, std::vector<Point *> *junctions_s) {
  std::vector<Point *> paths;
  std::vector<Point *> past_points;
  past_points.push_back(&departure);

  Point *tmp = &departure;

  do {
    std::vector<Point *> neighbors;

    for (int i = 0; i < voronoi_points.size(); i++) {
      Point *p = voronoi_points.at(i);
      double val = sqrt((tmp->getX() - p->getX()) * (tmp->getX() - p->getX()) +
                        (tmp->getY() - p->getY()) * (tmp->getY() - p->getY()));

      bool passato = false;
      for (int i = 0; i < past_points.size(); i++) {
        if (p == past_points.at(i)) passato = true;
      }

      if (val <= search_radius && !passato) neighbors.push_back(p);
    }

    if (neighbors.size() > 0) {
      double dist = std::numeric_limits<double>::infinity();
      Point *temp;
      for (int i = 0; i < neighbors.size(); i++) {
        Point *neighbor = neighbors.at(i);
        double val = sqrt((neighbor->getX() - arrival.getX()) *
                              (neighbor->getX() - arrival.getX()) +
                          (neighbor->getY() - arrival.getY()) *
                              (neighbor->getY() - arrival.getY()));
        if (val < dist) {
          temp = neighbor;
          dist = val;
        }
      }

      if (dist < Obstacle::Distance(*tmp, arrival))  // control to avoid removal
        tmp = temp;
      else
        goto alternative;

      paths.push_back(tmp);
      past_points.push_back(tmp);
    } else {
    alternative:
      std::cout << "[-] Failed, try again" << std::endl;

      paths.clear();
      past_points.clear();
      Point *junction_neighbor = NULL;

      double dist = std::numeric_limits<double>::infinity();
      for (int i = 0; i < junctions.size(); i++) {
        Point *inc = junctions.at(i);
        double val = Obstacle::Distance(*inc, arrival);
        bool present = false;
        if (junctions_s != NULL)
          for (int j = 0; j < junctions_s->size(); j++) {
            if (inc == junctions_s->at(j)) {
              present = true;
              break;
            }
          }
        if (val < dist && !present) {
          junction_neighbor = inc;
          dist = val;
        }
      }

      if (junction_neighbor == NULL) {
        std::cout << "[-] Could not find a paths..." << std::endl;
        exit(-1);
      }

      std::cout << "[~] Junction neighbor choice: " << junction_neighbor->getX()
                << " " << junction_neighbor->getY();

      if (junctions_s == NULL) {
        std::vector<Point *> chosen_junctions;
        junctions_s = &chosen_junctions;
      }

      junctions_s->push_back(junction_neighbor);
      paths = getVoronoiPath(departure, *junction_neighbor, junctions_s);

      std::vector<Point *> remaining =
          getVoronoiPath(*junction_neighbor, arrival, junctions_s);

      paths.insert(paths.end(), remaining.begin(), remaining.end());
      return paths;
    }

  } while (!(tmp->getX() == arrival.getX() && tmp->getY() == arrival.getY()));

  return paths;
}

std::vector<Point *> Voronoi::getVoronoiPath2(Point departure, Point arrival) {
  std::vector<Point *> paths;

  Point *junctions_departure;
  Point *junctions_arrival;

  double dist1 = 10000;
  double dist2 = 10000;
  for (int i = 0; i < junctions.size(); i++) {
    Point *inc = junctions.at(i);
    double val = Obstacle::Distance(*inc, departure);
    double val2 = Obstacle::Distance(*inc, arrival);
    if (val < dist1) {
      dist1 = val;
      junctions_departure = inc;
    }
    if (val2 < dist2) {
      dist2 = val2;
      junctions_arrival = inc;
    }
  }

  dist1 = 10000;
  Point *junction_goal;
  for (int i = 0; i < junctions.size(); i++) {
    Point *inc = junctions.at(i);
    double val = Obstacle::Distance(*inc, *junctions_departure);
    double val2 = Obstacle::Distance(*inc, *junctions_arrival);
    if (fabs(val - val2) < dist1) {
      junction_goal = inc;
      dist1 = fabs(val - val2);
    }
  }

  paths = getVoronoiPath(departure, *junctions_arrival, NULL);

  std::vector<Point *> temp;

  temp = getVoronoiPath(*junctions_arrival, arrival, NULL);
  paths.insert(paths.end(), temp.begin(), temp.end());

  return paths;
}
