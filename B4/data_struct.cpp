#include "data_struct.hpp"
#include <iostream>
#include "../common/stream_handlers.hpp"

std::ostream & afanasiev::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << data.key1 << ',' << data.key2 << ',' << data.str << '\n';
  }
  return out;
}

std::istream & afanasiev::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);

  if (sentry)
  {
    int key1 = detail::read_key(in);
    detail::get_separator(in);
    int key2 = detail::read_key(in);
    detail::get_separator(in);

    std::string str;

    if (!getline(in, str))
    {
      in.setstate(std::istream::failbit);
      return in;
    }

    if (in.good())
    {
      data = {key1, key2, str};
    }
  }

  return in;
}

bool afanasiev::comparator(const DataStruct& data_struct1, const DataStruct& data_struct2)
{
  if (data_struct1.key1 != data_struct2.key1)
  {
    return data_struct1.key1 < data_struct2.key1;
  }

  if (data_struct1.key2 != data_struct2.key2)
  {
    return data_struct1.key2 < data_struct2.key2;
  }

  return data_struct1.str.length() < data_struct2.str.length();
}

int detail::read_key(std::istream& stream)
{
  stream >> stream::ignore_blanks;

  if (stream.peek() == '\n')
  {
    stream.setstate(std::istream::failbit);
  }

  int key = 0;

  if (!(stream >> key))
  {
    stream.setstate(std::istream::failbit);
  }

  stream >> stream::ignore_blanks;

  if (key > afanasiev::MAX_KEY || key < afanasiev::MIN_KEY || stream.peek() == '\n' || stream.eof())
  {
    stream.setstate(std::istream::failbit);
  }

  return key;
}

std::istream& detail::get_separator(std::istream& stream)
{
  char comma = ' ';
  stream >> stream::ignore_blanks >> comma;
  if (comma != ',')
  {
    stream.setstate(std::istream::failbit);
  }

  return stream;
}
