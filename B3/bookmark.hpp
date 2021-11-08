#ifndef B3_BOOKMARK_HPP
#define B3_BOOKMARK_HPP

#include <map>
#include <list>


namespace detail
{
  class Bookmark
  {
  public:
    using Record = std::pair<std::string, std::string>;
    using Book = std::list<Record>;
    using Iterator = Book::iterator;

    Iterator begin();
    Iterator end();
    void show(const Iterator& iterator);
    Iterator move_mark_to_the_next(Iterator& iterator);
    Iterator move_mark_to_the_previous(Iterator& iterator);
    Iterator move(Iterator& iterator, int n);
    Iterator remove(Iterator& iterator);
    Iterator change_record(Iterator& iterator, const Record& record);
    void insert(Iterator& iterator, const Record& record);
    void push_back(const Record& record);
    bool is_empty();

  private:
    Book book_;
  };
}

#endif //B3_BOOKMARK_HPP
