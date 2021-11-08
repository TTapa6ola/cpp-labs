#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t&, double);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t&) override;
  void move(double, double) override;
private:
  point_t center_;
  double radius_;
};

#endif //A1_CIRCLE_HPP
