#ifndef B3_HANDLE_COMMANDS_HPP
#define B3_HANDLE_COMMANDS_HPP

#include <map>
#include <sstream>
#include "bookmark_interface.hpp"

namespace commands
{
  const char* const INVALID_COMMAND = "<INVALID COMMAND>\n";
  const char* const INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
  const char* const INVALID_STEP = "<INVALID STEP>\n";
  const char* const EMPTY = "<EMPTY>\n";

  bool get_name_correctly(std::string& name);
  bool get_mark_name_correctly(std::string& mark_name);
  void add(std::stringstream& stream, detail::BookmarkInterface& bookmark);
  void store(std::stringstream& stream, detail::BookmarkInterface& bookmark);
  void insert(std::stringstream& stream, detail::BookmarkInterface& bookmark);
  void delete_record(std::stringstream& stream, detail::BookmarkInterface& bookmark);
  void show(std::stringstream& stream, detail::BookmarkInterface& bookmark);
  void move(std::stringstream& stream, detail::BookmarkInterface& bookmark);

  const std::map<std::string, void(*)(std::stringstream&, detail::BookmarkInterface&)> commands
  ({
    {"add", add},
    {"store", store},
    {"insert", insert},
    {"delete", delete_record},
    {"show", show},
    {"move", move}
  });
}

#endif //B3_HANDLE_COMMANDS_HPP
