#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"

afanasiev::Rectangle::Rectangle(double width, double height, const point_t& pos, double angle):
  width_(width),
  height_(height),
  pos_(pos),
  angle_(angle)
{
  if (width_ < 0)
  {
    throw std::invalid_argument("Invalid width, value less than 0");
  }

  if (height_ < 0)
  {
    throw std::invalid_argument("Invalid height, value less than 0");
  }

  rotate(angle);
}

double afanasiev::Rectangle::getArea() const
{
  return width_ * height_;
}

afanasiev::point_t afanasiev::Rectangle::getCenter() const
{
  return pos_;
}

afanasiev::rectangle_t afanasiev::Rectangle::getFrameRect() const
{
  if (angle_ == 0)
  {
    return {width_, height_, pos_};
  }

  double width = std::max(width_ * cos(angle_), height_ * sin(angle_));
  double height = std::max(height_ * cos(angle_), width_ * sin(angle_));

  return {width, height, pos_};
}

void afanasiev::Rectangle::move(const point_t &point)
{
  pos_ = point;
}

void afanasiev::Rectangle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void afanasiev::Rectangle::scale(double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Invalid coefficient, value less then 0");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void afanasiev::Rectangle::rotate(double angle)
{
  angle_ = fmod(angle_ + (angle * M_PI / 180), 2 * M_PI);
}
