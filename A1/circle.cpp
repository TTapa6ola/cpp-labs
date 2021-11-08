#include "base-types.hpp"
#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t& center, double radius):
  center_(center),
  radius_(radius)
{
  assert(radius > 0);
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void Circle::move(const point_t& point)
{
  center_.x += point.x;
  center_.y += point.y;
}

void Circle::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
}
