#ifndef A2_BASE_TYPES_HPP
#define A2_BASE_TYPES_HPP

namespace afanasiev
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };
  bool areRectanglesIntersected(const rectangle_t& rectangle1, const rectangle_t& rectangle2);
}

#endif //A2_BASE_TYPES_HPP
