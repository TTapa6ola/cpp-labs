#ifndef A2_CIRCLE_HPP
#define A2_CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace afanasiev
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, double radius);
    double getArea() const override;
    point_t getCenter() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double x, double y) override;
    void scale(double coefficient) override;
    void rotate(double angle) override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif //A2_CIRCLE_HPP
