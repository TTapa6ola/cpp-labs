#ifndef B3_BOOKMARKINTERFACE_HPP
#define B3_BOOKMARKINTERFACE_HPP

#include "bookmark.hpp"

namespace detail
{
  class BookmarkInterface
  {
  public:
    enum Position
    {
      before,
      after
    };

    enum Step
    {
      first,
      last
    };

    BookmarkInterface();

    void add(const Bookmark::Record& record);
    void store(const std::string& name, const std::string& new_name);
    void insert(const Position& position, const std::string& name, const Bookmark::Record& record);
    void remove(const std::string& name);
    void show(const std::string& name);
    void move(const std::string& name, int steps);
    void move(const std::string& name, const Step& step);
    bool is_mark_in_marks(const std::string& name);
    bool is_empty();

  private:
    using Marks = std::map<std::string, Bookmark::Iterator>;
    Marks marks_;
    Bookmark book_;
    void create_current();
  };
}

#endif //B3_BOOKMARKINTERFACE_HPP
