#include "Astar.h"

#include <iostream>
#include <limits>

std::vector<Vector2*> Astar::drawPathLines(std::vector<Vector2*> paths) {
  std::vector<Vector2*> pathLines;
  for (int i = 0; i < paths.size() - 1; i++) {
    float percentage = ((float)i / (float)(paths.size())) * 100;
    std::cout << "[!] Drawing Astar Paths: " << percentage << "% \r";
    pathLines.push_back(paths.at(i));
    Vector2* p1 = paths.at(i);
    Vector2* p2 = paths.at(i + 1);

    double p1x = paths.at(i)->getX();
    double p2x = p2->getX();
    double p1y = paths.at(i)->getY();
    double p2y = p2->getY();

    Vector2* tmp = p1;
    double tmp_x = tmp->getX();
    double tmp_y = tmp->getY();

    while (!(tmp->getX() == p2->getX() && tmp->getY() == p2->getY())) {
      pathLines.push_back(tmp);

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
  return pathLines;
}

std::vector<std::map<int, float>> Astar::calculateCost(
    std::vector<std::vector<int>> neighbors, std::vector<Vector2*> nodes) {
  std::vector<std::map<int, float>> costs;
  for (int i = 0; i < neighbors.size(); i++) {
    float percentage = ((float)i / (float)(neighbors.size())) * 100;
    std::cout << "[!] Calculating Costs: " << percentage << "% \r";
    std::map<int, float> cost;
    Vector2 p0 = *nodes.at(i);
    for (int j = 0; j < neighbors.at(i).size(); j++) {
      Vector2 p1 = *nodes.at(neighbors.at(i).at(j));
      float c = p0.distanceTo(p1);
      cost[j] = c;
    }
    costs.push_back(cost);
  }
  return costs;
}

std::vector<Vector2*> Astar::getPaths(Vector2* start, Vector2* goal,
                                      int startNodeID, int goalNodeID,
                                      std::vector<std::vector<int>> neighbors,
                                      std::vector<Vector2*> nodes) {
  // calculate cost
  std::vector<std::map<int, float>> costs = calculateCost(neighbors, nodes);
  std::cout<<"[+] Neighbors Costs Calculated"<<std::endl;

  // do astar things
  std::vector<Vector2*> paths = runAstar(startNodeID, goalNodeID, neighbors, nodes, costs);
  paths.insert(paths.begin(), start);
  paths.push_back(goal);

  std::vector<Vector2*> finalPath = drawPathLines(paths);
  return finalPath;
}

std::vector<Vector2*> Astar::runAstar(int startNodeID, int goalNodeID,
                                      std::vector<std::vector<int>> neighbors,
                                      std::vector<Vector2*> nodes,
                                      std::vector<std::map<int, float>> costs) {
  std::vector<Vector2*> paths;
  std::vector<float>
      totalCostTo;  // Total Cost from start node toward the node provided
  std::vector<int> openList;
  bool goalFound = false;
  std::map<int, int> parent;

  for (int i = 0; i < nodes.size(); i++) {
    if (i != startNodeID) {
      totalCostTo.push_back(std::numeric_limits<float>::infinity());
    } else {
      totalCostTo.push_back(0.0);
    }
  }

  openList.push_back(startNodeID);
  while (openList.size() > 0) {
    int currentNodeID = openList.at(0);
    for (int i = 0; i < neighbors.at(currentNodeID).size(); i++) {
      int neighborNodeID = neighbors.at(currentNodeID).at(i);
      float newTotalCost =
          totalCostTo.at(currentNodeID) + costs.at(currentNodeID)[i];
      if (totalCostTo.at(neighborNodeID) > newTotalCost) {
        if (goalFound == true) {
          if (totalCostTo.at(neighborNodeID) < totalCostTo.at(goalNodeID)) {
            parent[neighborNodeID] = currentNodeID;
            totalCostTo.at(neighborNodeID) = newTotalCost;
            openList.push_back(neighborNodeID);
          }
        } else {
          parent[neighborNodeID] = currentNodeID;
          totalCostTo.at(neighborNodeID) = newTotalCost;
          openList.push_back(neighborNodeID);
        }
      }
      if (neighborNodeID == goalNodeID) {
        // goal found
        goalFound = true;
        // break;
      }
    }
    openList.erase(openList.begin());
    if (goalFound) {
      openList.clear();
    }
  }
  if (!goalFound) {
    std::cout << ("[!] Astar: No Available Path") << std::endl;
    paths.clear();
    return paths;
  }

  // print("\nReverse path: ");
  int prevNode = parent[goalNodeID];
  paths.insert(paths.begin(), nodes.at(goalNodeID));
  // print(goalID, " ");
  while (prevNode > 0) {
    paths.insert(paths.begin(), nodes.at(prevNode));
    prevNode = parent[prevNode];
  }
  return paths;
}