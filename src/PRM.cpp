#include "PRM.h"

#include <algorithm>

#include "Random.h"

PRM::PRM(double maxX, double maxY, std::vector<Obstacle*> obstacles) {
  this->maxX = maxX;
  this->maxY = maxY;
  size = 0;
  nodeSize = 0;
  this->obstacles = obstacles;
}

bool PRM::nodeInObstacles(Vector2* node) {
  for (int i = 0; i < obstacles.size(); i++) {
    std::vector<Vector2*> vertices = obstacles.at(i)->getVertices();
    Vector2* boxBottomLeft = vertices.at(0);
    Vector2* boxTopLeft = vertices.at(1);
    Vector2* boxTopRight = vertices.at(2);

    if (node->getX() > (boxTopLeft->getX() - nodeBostacleOffset) &&
        node->getX() < (boxTopRight->getX() + nodeBostacleOffset) &&
        node->getY() < (boxTopLeft->getY() + nodeBostacleOffset) &&
        node->getY() > (boxBottomLeft->getY() - nodeBostacleOffset)) {
      return true;
    }
  }
  return false;
}

bool PRM::nodeExists(Vector2* node) {
  for (Vector2* p : nodes) {
    if (p->getX() == node->getX() || p->getY() == node->getY()) {
      return true;
    }
  }
  return false;
}

void PRM::generateRandomNodes() {
  // generate random nodes
  for (int i = 0; i < maxNodes; i++) {
    float percentage = ((float)i / (float)(maxNodes)) * 100;
    std::cout << "[!] Generating Random Nodes: " << percentage << "% \r";
    Vector2* node;
    while (true) {
      node = new Vector2(Random::generateRand(0, maxX),
                         Random::generateRand(0, maxX));
      bool insideAnyObstacle = nodeInObstacles(node);
      if (!insideAnyObstacle) {
        break;
      }
    }
    nodes.push_back(node);
    nodeSize++;
  }
}

std::vector<Vector2*> PRM::getPaths(Vector2* starting, Vector2* goal,
                                    std::vector<Obstacle*> obstacles) {
  generateRandomNodes();
  std::cout << "[+] Random Nodes Generated." << std::endl;
  std::vector<std::vector<int>> neighbors = connectNeighbors();
  std::cout << "[+] Neighbors Connected." << std::endl;
  drawNeighborsPath(neighbors);
  std::cout << "[+] Path Drawn" << std::endl;
  return paths;
}

std::vector<Vector2*> PRM::getNodes() { return nodes; }

bool PRM::obstaclesHitWithRay(Vector2 ray_start, Vector2 ray_dir,
                              float distBetween) {
  for (int i = 0; i < obstacles.size(); i++) {
    std::vector<Vector2*> vertices = obstacles.at(i)->getVertices();
    Vector2 boxBottomLeft = *vertices.at(0);
    Vector2 boxTopLeft = *vertices.at(1);
    Vector2 boxTopRight = *vertices.at(2);
    bool hit = obstacleHitWithRay(ray_start, ray_dir, distBetween,
                                  boxBottomLeft, boxTopLeft, boxTopRight);
    if (hit == true) {
      return true;
    }
  }
  return false;
}

bool PRM::obstacleHitWithRay(Vector2 ray_start, Vector2 ray_dir,
                             float distBetween, Vector2 boxBottomLeft,
                             Vector2 boxTopLeft, Vector2 boxTopRight) {
  float obstacleWidth = boxTopRight.x - boxTopLeft.x;
  float t_left_x, t_right_x, t_top_y, t_bot_y;

  t_left_x = (boxTopLeft.x - ray_start.x) / ray_dir.x;
  t_right_x = (boxTopRight.x - ray_start.x) / ray_dir.x;
  t_top_y = (boxTopLeft.y - ray_start.y) / ray_dir.y;
  t_bot_y = (boxBottomLeft.y - ray_start.y) / ray_dir.y;

  float t_max_x = std::max(t_left_x, t_right_x);
  float t_max_y = std::max(t_top_y, t_bot_y);
  float t_max = std::min(t_max_x, t_max_y);  // When the ray exists the box

  float t_min_x = std::min(t_left_x, t_right_x);
  float t_min_y = std::min(t_top_y, t_bot_y);
  float t_min = std::max(t_min_x, t_min_y);  // When the ray enters the box

  // The the box is behind the ray (negative t)
  if (t_max < 0) {
    return false;
  }

  // The ray never hits the box
  if (t_min > t_max) {
    return false;
  }

  // The ray hits, but further out than max_t
  if (t_min > distBetween) {
    return false;
  }

  return true;
}

std::vector<std::vector<int>> PRM::connectNeighbors() {
  std::vector<std::vector<int>> neighbors;
  for (int i = 0; i < nodeSize; i++) {
    float percentage = ((float)i / (float)(nodeSize)) * 100;
    std::cout << "[!] Connecting Neighbors: " << percentage << "% \r";
    std::vector<int> nei;
    for (int j = 0; j < nodeSize; j++) {
      if (i == j) {
        continue;  // don't connect to myself
      } else if (nodes.at(i)->x == nodes.at(j)->x &&
                 nodes.at(i)->y == nodes.at(j)->y) {
        continue;
      }
      Vector2 dir = nodes.at(i)->directionTo(*nodes.at(j));
      float distBetween = nodes.at(i)->distanceTo(*nodes.at(j));
      if (distBetween <= 200) {
        bool obstaclesHitCheck =
            obstaclesHitWithRay(*nodes.at(i), dir, distBetween);
        if (obstaclesHitCheck == false) {
          nei.push_back(j);
        }
      }
    }
    neighbors.push_back(nei);
  }
  return neighbors;
}

void PRM::drawNeighborsPath(std::vector<std::vector<int>> neighbors) {
  for (int i = 0; i < neighbors.size(); i++) {
    float percentage = ((float)i / (float)(neighbors.size())) * 100;
    std::cout << "[!] Drawing Paths: " << percentage << "% \r";
    paths.push_back(nodes.at(i));
    for (int j = 0; j < neighbors.at(i).size(); j++) {
      Vector2* p1 = nodes.at(i);
      Vector2* p2 = nodes.at(neighbors.at(i).at(j));

      double p1x = nodes.at(i)->getX();
      double p2x = p2->getX();
      double p1y = nodes.at(i)->getY();
      double p2y = p2->getY();

      Vector2* tmp = p1;
      double tmp_x = tmp->getX();
      double tmp_y = tmp->getY();

      while (!(tmp->getX() == p2->getX() && tmp->getY() == p2->getY())) {
        paths.push_back(tmp);

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
      }
    }
  }
}

int PRM::getPathsSize() { return size; }

int PRM::getNodeSize() { return nodeSize; }