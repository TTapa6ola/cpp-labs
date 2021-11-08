#include "shape.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/io/ios_state.hpp>
#include "../common/stream_handlers.hpp"

std::list<std::string> detail::errors;

std::istream& detail::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  int x = 0;
  int y = 0;

  if (sentry)
  {
    boost::io::ios_flags_saver ios_flags_saver(in);
    in >> std::noskipws >> stream::ignore_blanks;
    if (in.get() != '(')
    {
      errors.push_front("point: expected '('");
      in.setstate(std::istream::failbit);
      return in;
    }

    if (!(in >> stream::ignore_blanks >> x >> stream::ignore_blanks))
    {
      errors.push_front("point: expected integer x");
      return in;
    }

    if (in.get() != ';')
    {
      errors.push_front("point: expected ';'");
      in.setstate(std::istream::failbit);
      return in;
    }

    if (!(in >> stream::ignore_blanks >> y >> stream::ignore_blanks))
    {
      errors.push_front("point: expected integer y");
      return in;
    }

    if (in.get() != ')')
    {
      errors.push_front("point: expected ')'");
      in.setstate(std::istream::failbit);
      return in;
    }

    if (in.good())
    {
      point = {x, y};
    }
  }
  return in;
}

std::ostream& detail::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << " (" << point.x << ";" << point.y << ")";
  }
  return out;
}

std::istream& detail::operator>>(std::istream& in, Shape& shape)
{
  std::istream::sentry sentry(in);
  Shape temp;

  if (sentry)
  {
    boost::io::ios_flags_saver ios_flags_saver(in);
    size_t vertices = 0;
    in >> vertices >> std::noskipws;

    if (vertices < 3)
    {
      errors.push_front("shape: invalid number of vertices");
      in.setstate(std::istream::failbit);
      return in;
    }

    Point point{0, 0};

    for (size_t i = 0; i < vertices; ++i)
    {
      if (!(in >> point))
      {
        errors.push_front("shape: incorrect point or lack of points");
        return in;
      }
      temp.push_back(point);
    }

    if (in.good())
    {
      shape = std::move(temp);
    }
  }

  return in;
}

std::ostream& detail::operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << shape.size() << ' ';
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  }
  return out;
}

bool detail::is_square(const Shape& shape)
{
  return is_rect(shape) && get_distance(shape[0], shape[1]) == get_distance(shape[1], shape[2]);
}

bool detail::is_rect(const Shape& shape)
{
  return shape.size() == 4 && get_distance(shape[0], shape[2]) == get_distance(shape[1], shape[3])
      && get_distance(shape[1], shape[2]) == get_distance(shape[0], shape[3])
      && get_distance(shape[0], shape[1]) == get_distance(shape[2], shape[3]);
}

double detail::get_distance(const Point& point1, const Point& point2)
{
  return std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2);
}

bool detail::comparator(const Shape& shape1, const Shape& shape2)
{
  if ((shape1.size() == 4) && (shape2.size() == 4) && (is_square(shape1) != is_square(shape2)))
  {
    return is_square(shape1);
  }

  return shape1.size() < shape2.size();
}
