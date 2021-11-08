#include "handle_commands.hpp"
#include <iostream>
#include <stdexcept>

bool commands::get_name_correctly(std::string& name)
{
  if ((name.front() != '\"') || (name.back() != '\"') || name.empty())
  {
    return false;
  }

  name.erase(name.begin());

  size_t i = 0;
  while ((i < name.size()) && (name[i] != '\"'))
  {
    if (name[i] == '\\')
    {
      if ((name[i + 1] == '\"') && (i < name.size() - 2))
      {
        name.erase(i, 1);
      }
      else
      {
        return false;
      }
    }
    ++i;
  }

  if (i == name.size())
  {
    return false;
  }
  name.erase(i);

  if (name.empty())
  {
    return false;
  }

  return true;
}

bool commands::get_mark_name_correctly(std::string& mark_name)
{
  if (mark_name.empty())
  {
    return false;
  }

  for (typename std::string::iterator i = mark_name.begin(); i != mark_name.end(); ++i)
  {
    if (((*i) != '-') && !std::isalnum(*i))
    {
      return false;
    }
  }

  return true;
}

void commands::add(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string number;
  std::string name;

  stream >> number;
  std::getline(stream >> std::ws, name);

  if (!get_name_correctly(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }

  detail::Bookmark::Record record(name, number);
  bookmark.add(record);
}

void commands::store(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string name;
  std::string new_name;

  stream >> name;
  stream >> std::ws;
  stream >> new_name;

  if (bookmark.is_mark_in_marks(name))
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }

  if (!get_mark_name_correctly(new_name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }

  bookmark.store(name, new_name);
}

void commands::insert(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string position;
  std::string mark;
  std::string number;
  std::string name;

  stream >> position;
  stream >> std::ws;
  stream >> mark;
  stream >> std::ws;
  stream >> number;
  std::getline(stream >> std::ws, name);

  if ((position != "before" && position != "after") || !get_name_correctly(name))
  {
    std::cout << INVALID_COMMAND;
    return;
  }

  if (bookmark.is_mark_in_marks(mark) && !bookmark.is_empty())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }

  detail::Bookmark::Record record(name, number);
  detail::BookmarkInterface::Position pos = position == "before" ? detail::BookmarkInterface::Position::before
      : detail::BookmarkInterface::Position::after;

  bookmark.insert(pos, mark, record);
}

void commands::delete_record(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string mark;
  stream >> mark;

  if (bookmark.is_mark_in_marks(mark))
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }

  bookmark.remove(mark);
}

void commands::show(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string mark;
  stream >> std::ws;
  stream >> mark;

  if (bookmark.is_mark_in_marks(mark) && mark != "current")
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }

  bookmark.show(mark);
}

void commands::move(std::stringstream& stream, detail::BookmarkInterface& bookmark)
{
  std::string mark;
  std::string step;

  stream >> mark;
  stream >> std::ws;
  stream >> step;

  if (bookmark.is_mark_in_marks(mark))
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }

  if (step != "first" && step != "last")
  {
    try
    {
      std::stoi(step);
    }
    catch (const std::invalid_argument& error)
    {
      std::cout << commands::INVALID_STEP;
      return;
    }

    bookmark.move(mark, std::stoi(step));
    return;
  }

  detail::BookmarkInterface::Step step1 = step == "first" ? detail::BookmarkInterface::Step::first
      : detail::BookmarkInterface::Step::last;

  bookmark.move(mark, step1);
}
