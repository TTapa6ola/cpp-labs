#include "tasks.hpp"
#include "handling_commands.hpp"

void tasks::first_task()
{
  afanasiev::QueueWithPriority<std::string> queue;
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
      commands::commands.at(command)(stream, queue);
    }
    else
    {
      std::cout << commands::INVALID_COMMAND;
    }
  }
}

void tasks::second_task()
{
  std::list<int> list;
  int num;

  while(std::cin >> num)
  {
    if ((num < 1) || (num > 20))
    {
      throw std::invalid_argument("Number must be less then 21 and more than 0");
    }

    list.push_back(num);
  }

  if (!std::cin.eof() && std::cin.bad())
  {
    throw std::runtime_error("Something went wrong while reading file");
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Entered is not an integer");
  }

  if (list.size() > 20)
  {
    throw std::invalid_argument("The length of the sequence must be less then 21");
  }

  recursive_print(list.begin(), --list.end());
}

void tasks::recursive_print(std::list<int>::iterator begin, std::list<int>::iterator end)
{
  if (begin != end)
  {
    std::cout << *begin << ' ';
    std::cout << *end << ' ';
    if (begin != --end)
    {
      recursive_print(++begin, end);
    }
    else
    {
      std::cout << '\n';
      return;
    }
  }
  else
  {
    if (*begin != 0)
    {
      std::cout << *begin << '\n';
    }
    return;
  }
}
