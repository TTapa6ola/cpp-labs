#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"

afanasiev::CompositeShape::CompositeShape():
  size_(0),
  array_(nullptr)
{}

afanasiev::CompositeShape::CompositeShape(const afanasiev::CompositeShape& composite_shape):
  size_(composite_shape.size_),
  array_(std::make_unique<ShapePointer[]>(size_))
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = composite_shape[i];
  }
}

afanasiev::CompositeShape::CompositeShape(afanasiev::CompositeShape&& composite_shape) noexcept:
  size_(composite_shape.size_),
  array_(std::move(composite_shape.array_))
{
  composite_shape.size_ = 0;
  composite_shape.array_.reset();
}

afanasiev::CompositeShape& afanasiev::CompositeShape::operator=(const afanasiev::CompositeShape& composite_shape)
{
  if (&composite_shape == this)
  {
    return *this;
  }

  size_ = composite_shape.getSize();
  array_ = std::make_unique<ShapePointer[]>(size_);

  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = composite_shape[i];
  }

  return *this;
}

afanasiev::CompositeShape& afanasiev::CompositeShape::operator=(afanasiev::CompositeShape&& composite_shape) noexcept
{
  if (&composite_shape == this)
  {
    return *this;
  }

  size_ = composite_shape.size_;
  array_ = std::move(composite_shape.array_);
  composite_shape.size_ = 0;
  composite_shape.array_.reset();

  return *this;
}

const afanasiev::Shape::ShapePointer afanasiev::CompositeShape::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Index out of array");
  }

  return array_[index];
}

double afanasiev::CompositeShape::getArea() const
{
  double area = 0.0;

  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }

  return area;
}

size_t afanasiev::CompositeShape::getSize() const
{
  return size_;
}

afanasiev::point_t afanasiev::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

afanasiev::rectangle_t afanasiev::CompositeShape::getFrameRect() const
{
  if (!array_)
  {
    return {-1.0, -1.0, {0.0, 0.0}};
  }

  size_t first_index = 0;

  for (first_index = 0; first_index < size_; first_index++)
  {
    if (array_[first_index]->getFrameRect().width != -1.0)
    {
      break;
    }
  }

  if (first_index == size_)
  {
    return {-1.0, -1.0, {0.0, 0.0}};
  }

  rectangle_t rectangle = array_[first_index]->getFrameRect();

  double left_side = rectangle.pos.x - rectangle.width / 2;
  double right_side = rectangle.pos.x + rectangle.width / 2;
  double down_side = rectangle.pos.y - rectangle.height / 2;
  double upper_side = rectangle.pos.y + rectangle.height / 2;

  for (first_index++; first_index < size_; first_index++)
  {
    rectangle = array_[first_index]->getFrameRect();

    if (rectangle.width == -1.0)
    {
      continue;
    }

    left_side = std::min(rectangle.pos.x - rectangle.width / 2, left_side);
    right_side = std::max(rectangle.pos.x + rectangle.width / 2, right_side);
    down_side = std::min(rectangle.pos.y - rectangle.height / 2, down_side);
    upper_side = std::max(rectangle.pos.y + rectangle.height / 2, upper_side);
  }

  double width = right_side - left_side;
  double height = upper_side - down_side;
  point_t center{(right_side + left_side) / 2, (upper_side + down_side) / 2};

  return {width, height, center};
}

void afanasiev::CompositeShape::move(double x, double y)
{
  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(x, y);
  }
}

void afanasiev::CompositeShape::move(const point_t& point)
{
  move(point.x - getCenter().x, point.y - getCenter().y);
}

void afanasiev::CompositeShape::scale(double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Invalid coefficient, value less then 0");
  }

  if ((size_ == 0) || (coefficient == 1))
  {
    return;
  }

  point_t frameCenter = getCenter();

  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->scale(coefficient);

    point_t shapeCenter = array_[i]->getCenter();
    double dx = shapeCenter.x - frameCenter.x;
    double dy = shapeCenter.y - frameCenter.y;

    array_[i]->move(dx * (coefficient - 1), dy * (coefficient - 1));
  }
}

void afanasiev::CompositeShape::rotate(double angle)
{
  point_t frame_center = getCenter();

  for (size_t i = 0; i < size_; i++)
  {
    rectangle_t rectangle = array_[i]->getFrameRect();

    double x1 = rectangle.pos.x - frame_center.x;
    double y1 = rectangle.pos.y - frame_center.y;
    double x2 = frame_center.x + x1 * cos(angle * M_PI / 180) - y1 * sin(angle * M_PI / 180);
    double y2 = frame_center.y + y1 * cos(angle * M_PI / 180) + x1 * sin(angle * M_PI / 180);

    array_[i]->move({x2, y2});

    array_[i]->rotate(angle);
  }
}

void afanasiev::CompositeShape::pushBack(const ShapePointer shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid shape, it can`t be nullptr");
  }

  ShapeArray array(std::make_unique<ShapePointer[]>(size_ + 1));

  for (size_t i = 0; i < size_; i++)
  {
    array[i] = array_[i];
  }

  array[size_] = shape;
  size_++;

  array_ = std::move(array);
}

void afanasiev::CompositeShape::deleteShape(size_t index)
{
  if (index >= size_)
  {
    throw std::invalid_argument("Invalid value, index must be less than size");
  }

  ShapeArray array(std::make_unique<ShapePointer[]>(size_ - 1));

  for (size_t i = 0; i < size_; i++)
  {
    if (i == index)
    {
      continue;
    }

    if (i < index)
    {
      array[i] = array_[i];
    }
    else
    {
      array[i - 1] = array_[i];
    }
  }

  size_--;

  array_ = std::move(array);
}
