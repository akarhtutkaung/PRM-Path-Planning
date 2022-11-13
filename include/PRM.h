#include <math.h>

#include <iostream>
#include <vector>

#include "Obstacle.h"

class PRM {
 private:
  int maxX;
  int maxY;
  const int maxNodes = 200;
  const int nodeBostacleOffset = 2;
  int size;
  int nodeSize;
  std::vector<Vector2*> nodes;
  std::vector<Vector2*> paths;
  std::vector<Obstacle*> obstacles;
  void generateRandomNodes();
  bool nodeInObstacles(Vector2* node);
  bool nodeExists(Vector2* node);
  std::vector<std::vector<int>> connectNeighbors();
  void drawNeighborsPath(std::vector<std::vector<int>> neighbors);
  bool obstaclesHitWithRay(Vector2 ray_start, Vector2 ray_dir, float distBetween);
  bool obstacleHitWithRay(Vector2 ray_start, Vector2 ray_dir, float distBetween, Vector2 boxBottomLeft, Vector2 boxTopLeft, Vector2 boxTopRight);

 public:
  PRM(double maxX, double maxY, std::vector<Obstacle*> obstacles);
  std::vector<Vector2*> getPaths(Vector2* starting, Vector2* goal, std::vector<Obstacle*> obstacles);
  int getPathsSize();
  int getNodeSize();
  std::vector<Vector2*> getNodes();
};