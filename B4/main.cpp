#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data_struct.hpp"

int main()
{
  try
  {
    std::vector <afanasiev::DataStruct> vector{std::istream_iterator<afanasiev::DataStruct>(std::cin),
                                               std::istream_iterator<afanasiev::DataStruct>()};

    if (!std::cin.eof())
    {
      return 1;
    }

    std::sort(vector.begin(), vector.end(), afanasiev::comparator);
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<afanasiev::DataStruct>(std::cout));
  }
  catch (std::exception& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (...)
  {
    return 2;
  }

 return 0;
}
