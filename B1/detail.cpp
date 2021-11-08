#include "detail.hpp"
#include <random>

void detail::fillRandom(double* array, int size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  for (int i = 0; i < size; i++)
  {
    array[i] = dist(gen);
  }
}
