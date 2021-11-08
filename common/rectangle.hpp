#ifndef A2_RECTANGLE_HPP
#define A2_RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace afanasiev
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& pos, double angle = 0.0);
    double getArea() const override;
    point_t getCenter() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double x, double y) override;
    void scale(double coefficient) override;
    void rotate(double angle) override;
  private:
    double width_;
    double height_;
    point_t pos_;
    double angle_;
  };
}

#endif //A2_RECTANGLE_HPP
