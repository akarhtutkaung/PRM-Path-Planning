/* Created by Simone Tinella, University of Catania*/
/* Modified into English wordings by Akar (Ace) Kaung, University of Minnesota*/

#include <fstream>
#include <iostream>
#include <vector>

#include "RRT.h"

const int maxX = 200;
const int maxY = 200;

int main() {
  
  std::vector<Point *> table1P;
  table1P.push_back(new Point(20, 140));
  table1P.push_back(new Point(20, 160));
  table1P.push_back(new Point(60, 160));
  table1P.push_back(new Point(60, 140));
  Obstacle *table1 = new Obstacle(&table1P);

  std::vector<Point *> table2P;
  table2P.push_back(new Point(20, 100));
  table2P.push_back(new Point(20, 120));
  table2P.push_back(new Point(60, 120));
  table2P.push_back(new Point(60, 100));
  Obstacle *table2 = new Obstacle(&table2P);

  std::vector<Point *> table3P;
  table3P.push_back(new Point(20, 60));
  table3P.push_back(new Point(20, 80));
  table3P.push_back(new Point(60, 80));
  table3P.push_back(new Point(60, 60));
  Obstacle *table3 = new Obstacle(&table3P);

  std::vector<Point *> table4P;
  table4P.push_back(new Point(20, 20));
  table4P.push_back(new Point(20, 40));
  table4P.push_back(new Point(60, 40));
  table4P.push_back(new Point(60, 20));
  Obstacle *table4 = new Obstacle(&table4P);

  std::vector<Point *> table5P;
  table5P.push_back(new Point(80, 140));
  table5P.push_back(new Point(80, 160));
  table5P.push_back(new Point(100, 160));
  table5P.push_back(new Point(100, 140));
  Obstacle *table5 = new Obstacle(&table5P);

  std::vector<Point *> table6P;
  table6P.push_back(new Point(80, 100));
  table6P.push_back(new Point(80, 120));
  table6P.push_back(new Point(100, 120));
  table6P.push_back(new Point(100, 100));
  Obstacle *table6 = new Obstacle(&table6P);

  std::vector<Point *> table7P;
  table7P.push_back(new Point(80, 60));
  table7P.push_back(new Point(80, 80));
  table7P.push_back(new Point(100, 80));
  table7P.push_back(new Point(100, 60));
  Obstacle *table7 = new Obstacle(&table7P);

  std::vector<Point *> table8P;
  table8P.push_back(new Point(80, 20));
  table8P.push_back(new Point(80, 40));
  table8P.push_back(new Point(100, 40));
  table8P.push_back(new Point(100, 20));
  Obstacle *table8 = new Obstacle(&table8P);

  std::vector<Point *> table9P;
  table9P.push_back(new Point(120, 140));
  table9P.push_back(new Point(120, 160));
  table9P.push_back(new Point(160, 160));
  table9P.push_back(new Point(160, 140));
  Obstacle *table9 = new Obstacle(&table9P);

  std::vector<Point *> table10P;
  table10P.push_back(new Point(120, 100));
  table10P.push_back(new Point(120, 120));
  table10P.push_back(new Point(160, 120));
  table10P.push_back(new Point(160, 100));
  Obstacle *table10 = new Obstacle(&table10P);

  std::vector<Point *> table11P;
  table11P.push_back(new Point(120, 60));
  table11P.push_back(new Point(120, 80));
  table11P.push_back(new Point(160, 80));
  table11P.push_back(new Point(160, 60));
  Obstacle *table11 = new Obstacle(&table11P);

  std::vector<Point *> table12P;
  table12P.push_back(new Point(120, 20));
  table12P.push_back(new Point(120, 40));
  table12P.push_back(new Point(160, 40));
  table12P.push_back(new Point(160, 20));
  Obstacle *table12 = new Obstacle(&table12P);

  std::vector<Obstacle *> obstacles;
  obstacles.push_back(table1);
  obstacles.push_back(table2);
  obstacles.push_back(table3);
  obstacles.push_back(table4);
  obstacles.push_back(table5);
  obstacles.push_back(table6);
  obstacles.push_back(table7);
  obstacles.push_back(table8);
  obstacles.push_back(table9);
  obstacles.push_back(table10);
  obstacles.push_back(table11);
  obstacles.push_back(table12);

  // Voronoi *map = new Voronoi(maxX, maxY, obstacles);
  // std::vector<Point *> *voronoi = map->getVoronoiPoints();
  // obstacles = *map->getobstacles();

  Point *depature = new Point(20, 180);
  Point *arrival = new Point(119, 30);
  // std::vector<Point> Paths = map->getPaths(*depature, *arrival);
  
  RRT* rrt = new RRT(maxX, maxY, obstacles);
  std::vector<Point*> randomPaths = rrt->getPaths(depature, arrival, obstacles);

  std::ofstream fobstacles("obstacles.txt");
  for (int i = 0; i < obstacles.size(); i++) {
    for (int j = 0; j < obstacles.at(i)->getClutter()->size(); j++) {
      fobstacles << obstacles.at(i)->getClutter()->at(j)->getX() << " "
                 << obstacles.at(i)->getClutter()->at(j)->getY() << std::endl;
    }
  }
  fobstacles.close();

  std::ofstream frandomPath("randomPaths.txt");
  for (int i = 0; i < rrt->getPathsSize(); i++) {
    frandomPath << randomPaths.at(i)->getX() << " " << randomPaths.at(i)->getY()
             << std::endl;
  }
  frandomPath.close();

  // std::ofstream fPaths("pathsToFollow.txt");
  // for (int i = 0; i < Paths.size(); i++) {
  //   fPaths << Paths.at(i).getX() << " " << Paths.at(i).getY() << std::endl;
  // }
  // fPaths.close();
}
