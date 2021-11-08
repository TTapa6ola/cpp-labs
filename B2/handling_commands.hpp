#ifndef B2_HANDLING_COMMANDS_HPP
#define B2_HANDLING_COMMANDS_HPP

#include <sstream>
#include <iostream>
#include "QueueWithPriority.hpp"

namespace commands
{
  const char *INVALID_COMMAND = "<INVALID COMMAND>\n";
  const char *EMPTY_COMMAND = "<EMPTY>";

  void add(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue);
  void get(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue);
  void accelerate(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue);

  const std::map<std::string, void(*)(std::stringstream&, afanasiev::QueueWithPriority<std::string>&)> commands
  ({
    {"add", add},
    {"get", get},
    {"accelerate", accelerate}
  });

  const std::map<std::string, afanasiev::QueueWithPriority<std::string>::ElementPriority> priorities
  ({
    {"high", afanasiev::QueueWithPriority<std::string>::ElementPriority::HIGH},
    {"normal", afanasiev::QueueWithPriority<std::string>::ElementPriority::NORMAL},
    {"low", afanasiev::QueueWithPriority<std::string>::ElementPriority::LOW}
  });

  void add(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue)
  {
    std::string priority;
    stream >> priority;

    if (priorities.count(priority) == 0)
    {
      std::cout << INVALID_COMMAND;
    }
    else
    {
      std::string value;
      getline(stream >> std::ws, value);

      if(value.empty())
      {
        std::cout << INVALID_COMMAND;
      }
      else
      {
        queue.put_element_to_queue(value, priorities.at(priority));
      }
    }
  }

  void get(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue)
  {
    stream >> std::ws;

    if (!stream.eof())
    {
      std::cout << commands::INVALID_COMMAND;
    }
    else
    {
      std::cout << ((queue.is_empty()) ? EMPTY_COMMAND : queue.get_element()) << '\n';
    }
  }

  void accelerate(std::stringstream& stream, afanasiev::QueueWithPriority<std::string>& queue)
  {
    stream >> std::ws;
    if (!stream.eof())
    {
      std::cout << commands::INVALID_COMMAND;
    }
    else
    {
      queue.accelerate();
    }
  }
}

#endif //B2_HANDLING_COMMANDS_HPP
