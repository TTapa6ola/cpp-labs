#include "stream_handlers.hpp"
#include <iostream>


std::istream& stream::ignore_blanks(std::istream& stream)
{
  while (stream.peek() == ' ' || stream.peek() == '\t')
  {
    stream.ignore();
  }

  return stream;
}
