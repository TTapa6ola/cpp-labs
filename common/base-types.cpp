#include "base-types.hpp"
#include <cmath>

bool afanasiev::areRectanglesIntersected(const afanasiev::rectangle_t& rectangle1, const afanasiev::rectangle_t& rectangle2)
{
  if ((rectangle1.width == -1.0) || (rectangle2.width == -1.0))
  {
    return false;
  }
  double d_x = fabs(rectangle1.pos.x - rectangle2.pos.x);
  double d_y = fabs(rectangle1.pos.y - rectangle2.pos.y);
  double d_width = rectangle1.width / 2 + rectangle2.width / 2;
  double d_height = rectangle1.height / 2 + rectangle2.height / 2;

  return (d_x <= d_width) && (d_y <= d_height);
}
