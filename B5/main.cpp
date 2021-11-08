#include <iostream>
#include <map>
#include <string>
#include "tasks.hpp"


static const std::map<std::string, int(*)()> TASKS
({
  {"1", tasks::task1},
  {"2", tasks::task2}
});

int main(int argc, char** argv)
{
  if (argc < 2 || argv[1] == nullptr)
  {
    std::cerr << "Expected task number";
    return 1;
  }

  try
  {
    if (TASKS.count(argv[1]))
    {
      return TASKS.at(argv[1])();
    }
    std::cerr << "Invalid task number";
    return 1;
  }
  catch (std::exception& error)
  {
    std::cerr << error.what();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error";
  }
  return 2;
}
