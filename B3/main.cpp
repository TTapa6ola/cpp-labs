#include <iostream>
#include "bookmark.hpp"
#include "tasks.hpp"

int main(int argc, char** argv)
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "There should be 1 parameter";
      return 1;
    }

    switch (std::stoi(argv[1]))
    {
    case 1:
      tasks::first_task();
      break;
    case 2:
      tasks::second_task();
      break;
    default:
      std::cerr << "There are just 2 tasks";
      return 1;
    }
  }
  catch (const std::logic_error& error)
  {
    std::cerr << error.what();
    return 1;
  }

  catch (const std::runtime_error& error)
  {
    std::cerr << error.what();
    return 2;
  }

  return 0;
}
