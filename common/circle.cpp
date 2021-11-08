#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

afanasiev::Circle::Circle(const point_t& center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0)
  {
    throw std::invalid_argument("Invalid radius, value less then 0");
  }
}

afanasiev::point_t afanasiev::Circle::getCenter() const
{
  return center_;
}

afanasiev::rectangle_t afanasiev::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

double afanasiev::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

void afanasiev::Circle::move(const point_t& point)
{
  center_ = point;
}

void afanasiev::Circle::move(double x, double y)
{
  center_.x += x;
  center_.y += y;
}

void afanasiev::Circle::scale(double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Invalid coefficient, value less then 0");
  }
  radius_ *= coefficient;
}

void afanasiev::Circle::rotate(double)
{}
