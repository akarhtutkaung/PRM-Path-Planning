#include "Vector2.h"
#include <vector>
#include <map>

class Astar {
  private:
    static std::vector<Vector2*> drawPathLines(std::vector<Vector2*> path);
    static std::vector<std::map<int, float>> calculateCost(std::vector<std::vector<int>> neighbors, std::vector<Vector2*> nodes);
    static std::vector<Vector2*> runAstar(int startNodeID, int goalNodeID, std::vector<std::vector<int>> neighbors, std::vector<Vector2*> nodes, std::vector<std::map<int, float>> costs);
  public:
    static std::vector<Vector2*> getPaths(Vector2* start, Vector2* goal, int startNodeID, int goalNodeID, std::vector<std::vector<int>> neighbors, std::vector<Vector2*> nodes);
};