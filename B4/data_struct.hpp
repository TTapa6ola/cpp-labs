#ifndef B4_DATA_STRUCT_HPP
#define B4_DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

namespace afanasiev
{
  const int MIN_KEY = -5;
  const int MAX_KEY = 5;

  struct DataStruct
  {
    int key1;
    int key2;
    std::string str;
  };

  std::istream& operator>>(std::istream& in, DataStruct & data);
  std::ostream& operator<<(std::ostream& out, const DataStruct & data);
  bool comparator(const DataStruct& data_struct1, const DataStruct& data_struct2);
}

namespace detail
{
  int read_key(std::istream& stream);
  std::istream& get_separator(std::istream& stream);
}

#endif //B4_DATA_STRUCT_HPP
