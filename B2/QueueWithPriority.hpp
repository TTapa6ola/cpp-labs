#ifndef B2_QUEUEWITHPRIORITY_HPP
#define B2_QUEUEWITHPRIORITY_HPP

#include <list>
#include <iostream>
#include <stdexcept>
#include <map>

namespace afanasiev
{
  template<typename T>
  class QueueWithPriority
  {
  public:
    typedef enum
    {
      LOW,
      NORMAL,
      HIGH
    } ElementPriority;

    QueueWithPriority() = default;
    ~QueueWithPriority() = default;

    void put_element_to_queue(T& element, ElementPriority priority);

    T get_element();

    void accelerate();
    bool is_empty();


  private:
    using QueueMap = std::map<ElementPriority, std::list<T>, std::greater<ElementPriority>>;
    QueueMap queue_;
  };

  template<typename T>
  void QueueWithPriority<T>::put_element_to_queue(T& element, ElementPriority priority)
  {
    queue_[priority].push_back(element);
  }

  template<typename T>
  T QueueWithPriority<T>::get_element()
  {
    T element;

    for (typename QueueMap::iterator iterator = queue_.begin(); iterator != queue_.end(); ++iterator)
    {
      if (!iterator->second.empty())
      {
        element = iterator->second.front();
        iterator->second.pop_front();
        break;
      }
    }

    return element;
  }

  template<typename T>
  void QueueWithPriority<T>::accelerate()
  {
    queue_[ElementPriority::HIGH].splice(queue_[ElementPriority::HIGH].end(), queue_[ElementPriority::LOW]);
  }

  template<typename T>
  bool QueueWithPriority<T>::is_empty()
  {
    for (typename QueueMap::iterator iterator = queue_.begin(); iterator != queue_.end(); ++iterator)
    {
      if (!iterator->second.empty())
      {
        return false;
      }
    }

    return true;
  }
}

#endif //B2_QUEUEWITHPRIORITY_HPP
