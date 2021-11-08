#include "iterator.hpp"
#include "factorial.hpp"

iterator::Iterator::Iterator():
        current_(1),
        index_(1)
{}

iterator::Iterator::Iterator(int index):
        current_(1),
        index_(1)
{
  if (index < factorial::Factorial::MIN_SIZE || index > factorial::Factorial::MAX_SIZE)
  {
    throw std::out_of_range("Invalid index, it must be in interval from 1 to 11");
  }

  for (int i = 0; i < index; ++i)
  {
    ++(*this);
  }
}

bool iterator::Iterator::operator==(const Iterator& iterator) const
{
  return current_ == iterator.current_;
}

bool iterator::Iterator::operator!=(const Iterator& iterator) const
{
  return current_ != iterator.current_;
}

int iterator::Iterator::operator*() const
{
  return current_;
}

int iterator::Iterator::operator->() const
{
  return current_;
}

iterator::Iterator& iterator::Iterator::operator++()
{
  current_ *= index_++;
  return *this;
}

iterator::Iterator iterator::Iterator::operator++(int)
{
  Iterator temp(*this);
  current_ *= index_++;
  return temp;
}

iterator::Iterator& iterator::Iterator::operator--()
{
  --index_;
  current_ /= index_;
  return *this;
}

iterator::Iterator iterator::Iterator::operator--(int)
{
  Iterator temp(*this);
  --index_;
  current_ /= index_;

  return temp;
}
