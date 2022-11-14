#include <random>

class Random {
 public:
  static int generateRand(int min, int max);
};

int Random::generateRand(int min, int max) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(min, max);
  return distr(generator);
}