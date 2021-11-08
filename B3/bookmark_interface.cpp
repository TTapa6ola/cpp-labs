#include "bookmark_interface.hpp"
#include <iostream>

detail::BookmarkInterface::BookmarkInterface()
{
  marks_["current"] = book_.begin();
}

void detail::BookmarkInterface::add(const Bookmark::Record& record)
{
  book_.push_back(record);
  create_current();
}

void detail::BookmarkInterface::store(const std::string& name, const std::string& new_name)
{
  marks_[new_name] = marks_[name];
}

void detail::BookmarkInterface::insert(const Position& position, const std::string& name, const Bookmark::Record& record)
{
  Bookmark::Iterator pos = (position == Position::after) ? std::next(marks_[name]) : marks_[name];

  book_.insert(pos, record);
  create_current();
}

void detail::BookmarkInterface::remove(const std::string& name)
{
  Bookmark::Iterator iterator = marks_[name];

  for (Marks::value_type& it : marks_)
  {
    if (it.second == iterator)
    {
      it.second = std::next(iterator) == book_.end() ? std::prev(iterator) : std::next(iterator);
    }
  }

  book_.remove(iterator);
}

void detail::BookmarkInterface::show(const std::string& name)
{
  if (book_.is_empty())
  {
    std::cout << "<EMPTY>\n";
  }

  book_.show(marks_[name]);
}

void detail::BookmarkInterface::move(const std::string& name, int steps)
{
  book_.move(marks_[name], steps);
}

void detail::BookmarkInterface::move(const std::string& name, const Step& step)
{
  marks_[name] = (step == Step::first) ? book_.begin() : --book_.end();
}

bool detail::BookmarkInterface::is_mark_in_marks(const std::string& name)
{
  return marks_.count(name) == 0;
}

bool detail::BookmarkInterface::is_empty()
{
  return book_.is_empty();
}

void detail::BookmarkInterface::create_current()
{
  if (std::next(book_.begin()) == book_.end())
  {
    marks_["current"] = book_.begin();
  }
}
