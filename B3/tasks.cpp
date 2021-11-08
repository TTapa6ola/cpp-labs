#include "tasks.hpp"
#include <iostream>
#include <algorithm>
#include "handle_commands.hpp"
#include "factorial.hpp"

void tasks::first_task()
{
  detail::BookmarkInterface bookmark;
  std::string command;

  while (getline(std::cin >> std::ws, command))
  {
    if (std::cin.bad())
    {
      throw std::runtime_error("Something went wrong while reading lines");
    }

    std::stringstream stream(command);
    stream >> command;
    if (commands::commands.count(command) != 0)
    {
      commands::commands.at(command)(stream, bookmark);
    }
    else
    {
      std::cout << commands::INVALID_COMMAND;
    }
  }
}

void tasks::second_task()
{
  factorial::Factorial factorial;

  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
}
