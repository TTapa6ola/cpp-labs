#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP

#include "iterator.hpp"

namespace factorial
{
  class Factorial
  {
  public:
    static const int MIN_SIZE = 1;
    static const int MAX_SIZE = 11;

    Factorial() = default;
    iterator::Iterator begin();
    iterator::Iterator end();
  };
}

#endif //B3_FACTORIAL_HPP
