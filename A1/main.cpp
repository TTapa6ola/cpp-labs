#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

void callShapeMethods(Shape&);

int main()
{
  Circle test_circle({2.0, 3.0}, 7.0);
  callShapeMethods(test_circle);
  Rectangle test_rectangle(1.0, 2.0, {4.0, 3.2});
  callShapeMethods(test_rectangle);
  return 0;
}

void callShapeMethods(Shape& shape)
{
  shape.getArea();
  shape.getFrameRect();
  shape.move({-1.0, -2.0});
  shape.move(2.0, 1.0);
}
