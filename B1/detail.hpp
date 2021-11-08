#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <vector>
#include <iostream>
#include <list>

namespace detail
{
  template<typename Container>
  struct IndexOperator
  {
    static size_t get_begin(Container&)
    {
      return 0;
    }

    static size_t get_end(Container& vector)
    {
      return vector.size();
    }

    static typename Container::reference get_value(Container& vector, size_t index)
    {
      return vector[index];
    }
  };

  template<typename Container>
  struct MethodAt
  {
    static size_t get_begin(Container&)
    {
      return 0;
    }

    static size_t get_end(Container& vector)
    {
      return vector.size();
    }

    static typename Container::reference get_value(Container& vector, size_t index)
    {
      return vector.at(index);
    }
  };

  template<typename Container>
  struct Iterator
  {
    static typename Container::iterator get_begin(Container& list)
    {
      return list.begin();
    }

    static typename Container::iterator get_end(Container& list)
    {
      return list.end();
    }

    static typename Container::reference get_value(Container&, typename Container::iterator index)
    {
      return *index;
    }
  };

  template<typename TaskType, typename Container>
  void sort(Container& container, bool order)
  {
    for (auto i = TaskType::get_begin(container); i != TaskType::get_end(container); i++)
    {
      for (auto j = i; j != TaskType::get_end(container); j++)
      {
        if ((TaskType::get_value(container, i) > TaskType::get_value(container, j)) == order)
        {
          std::swap(TaskType::get_value(container, i), TaskType::get_value(container, j));
        }
      }
    }
  }

  template<typename Container>
  void print(const Container& container)
  {
    for (auto i = container.begin(); i != container.end(); i++)
    {
      std::cout << *i << ' ';
    }

    std::cout << "\n";
  }

  void fillRandom(double* array, int size);
}

#endif // DETAIL_HPP
