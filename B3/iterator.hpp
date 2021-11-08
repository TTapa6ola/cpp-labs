#ifndef B3_ITERATOR_HPP
#define B3_ITERATOR_HPP

#include <iterator>

namespace iterator
{
  class Iterator: public std::iterator<std::bidirectional_iterator_tag, int>
  {
  public:
    Iterator();
    Iterator(int index);
    bool operator ==(const Iterator& iterator) const;
    bool operator !=(const Iterator& iterator) const;
    int operator*() const;
    int operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);

  private:
    int current_;
    int index_;
  };
}

#endif //B3_ITERATOR_HPP
