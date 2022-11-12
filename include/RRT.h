#include <math.h>

#include <iostream>
#include <vector>

#include "Obstacle.h"
#include "Random.h"

class RRT {
 private:
  int maxX;
  int maxY;
  const int maxNodes = 1000;
  int size;
  std::vector<Point*> nodes;
  std::vector<Point*> paths;
  std::vector<Obstacle*> obstacles;
  void generateRandomNodes();
  bool nodeInObstacles(Point* node);

 public:
  RRT(double maxX, double maxY, std::vector<Obstacle*> obstacles);
  std::vector<Point*> getPaths(Point* starting, Point* goal, std::vector<Obstacle*> obstacles);
  int getPathsSize();
};

RRT::RRT(double maxX, double maxY, std::vector<Obstacle*> obstacles) {
  this->maxX = maxX;
  this->maxY = maxY;
  size = 0;
  this->obstacles = obstacles;
}


bool RRT::nodeInObstacles(Point* node){
  for(int i=0; i<obstacles.size(); i++){
    
  }
}

void RRT::generateRandomNodes() {
  // generate random nodes
  for (int i = 0; i < maxNodes; i++) {
    float percentage = ((float)i / (float)(maxNodes)) * 100;
    std::cout << "[!] Generating Random Nodes: " << percentage << "% \r";
    Point* node;
    while(true){
      node = new Point(Random::generateRand(0, maxX), Random::generateRand(0, maxX));
      bool insideAnyObstacle = nodeInObstacles(node);
      if(!insideAnyObstacle){
        break;
      }
    } 
    nodes.push_back(node);
  }
}

std::vector<Point*> RRT::getPaths(Point* starting, Point* goal,
                                  std::vector<Obstacle*> obstacles) {
  generateRandomNodes();
  // connect the points
  return paths;
}

int RRT::getPathsSize() { return size; }