#include "bookmark.hpp"
#include <iostream>

detail::Bookmark::Iterator detail::Bookmark::begin()
{
  return book_.begin();
}

detail::Bookmark::Iterator detail::Bookmark::end()
{
  return book_.end();
}

void detail::Bookmark::show(const Iterator& iterator)
{
  if (is_empty())
  {
    return;
  }

  std::cout << iterator->second << " " << iterator->first << '\n';
}

detail::Bookmark::Iterator detail::Bookmark::move_mark_to_the_next(Iterator& iterator)
{
  if (std::next(iterator) == book_.end())
  {
    return iterator;
  }

  return ++iterator;
}

detail::Bookmark::Iterator detail::Bookmark::move_mark_to_the_previous(Iterator& iterator)
{
  if (iterator == book_.begin())
  {
    return iterator;
  }

  return --iterator;
}

detail::Bookmark::Iterator detail::Bookmark::move(Iterator& iterator, int n)
{
  int l_distance = std::distance(book_.begin(), iterator);
  int r_distance = std::distance(iterator, std::prev(book_.end()));

  if ((std::abs(n) > l_distance) && (n < 0))
  {
    iterator = book_.begin();
    return iterator;
  }

  if (n > r_distance)
  {
    iterator = std::prev(book_.end());
    return iterator;
  }

  std::advance(iterator, n);
  return iterator;
}

detail::Bookmark::Iterator detail::Bookmark::remove(Iterator& iterator)
{
  return book_.erase(iterator);
}

detail::Bookmark::Iterator detail::Bookmark::change_record(Iterator& iterator, const Record& record)
{
  *iterator = record;
  return iterator;
}

void detail::Bookmark::insert(Iterator& iterator, const Record& record)
{
  book_.insert(iterator, record);
}

void detail::Bookmark::push_back(const Record& record)
{
  book_.push_back(record);
}

bool detail::Bookmark::is_empty()
{
  return book_.empty();
}
