#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Wrong number of parameters, it must be from 1 to 3";
      return 1;
    }
    switch (std::stoi(argv[1]))
    {
    case 1:
      if (argc != 3)
      {
        std::cerr << "Wrong number of parameters, in 1st task there must be 3 parameters";
        return 1;
      }

      tasks::first_task(argv[2]);
      break;
    case 2:
      if (argc != 3)
      {
        std::cerr << "Wrong number of parameters, in 2nd task there must be 3 parameters";
        return 1;
      }

      tasks::second_task(argv[2]);
      break;
    case 3:
      if (argc != 2)
      {
        std::cerr << "Wrong number of parameters, in 3rd task there must be 2 parameters";
        return 1;
      }

      tasks::third_task();
      break;
    case 4:
      if (argc != 4)
      {
        std::cerr << "Wrong number of parameters, in 4th task there must be 4 parameters";
        return 1;
      }

      tasks::fourth_task(argv[2], std::stoi(argv[3]));
      break;
    default:
      std::cerr << "Wrong job number, it must be from 1 to 4";
      return 1;
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << error.what();
    return 1;
  }

  return 0;
}
