#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <vector>
#include <list>
#include <string>
#include <iosfwd>

namespace detail
{
  struct Point
  {
    int x, y;
  };

  using Shape = std::vector<Point>;
  extern std::list<std::string> errors;

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);

  std::istream& operator>>(std::istream& in, Shape& shape);
  std::ostream& operator<<(std::ostream& out, const Shape& shape);

  bool is_square(const Shape& shape);
  bool is_rect(const Shape& shape);
  double get_distance(const Point& point1, const Point& point2);
  bool comparator(const Shape& shape1, const Shape& shape2);
}

#endif //B5_SHAPE_HPP
