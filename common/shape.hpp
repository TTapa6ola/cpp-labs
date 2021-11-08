#ifndef A2_SHAPE_HPP
#define A2_SHAPE_HPP
#include <memory>

namespace afanasiev
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    using ShapePointer = std::shared_ptr<Shape>;
    using ShapeArray = std::unique_ptr<ShapePointer[]>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual point_t getCenter() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double x, double y) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double angle) = 0;
  };
}

#endif //A2_SHAPE_HPP
