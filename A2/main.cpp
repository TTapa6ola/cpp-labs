#include <iostream>
#include <stdexcept>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  afanasiev::Shape* shape = nullptr;
  try
  {
    shape = new afanasiev::Circle({2.0, 3.0}, 7.0);
    shape->getArea();
    shape->getFrameRect();
    shape->move({-1.0, -2.0});
    shape->move(2.0, 1.0);
    shape->scale(12.0);

    shape = new afanasiev::Rectangle(1.0, 2.0, {4.0, 3.2});
    shape->getArea();
    shape->getFrameRect();
    shape->move({-1.0, -2.0});
    shape->move(2.0, 1.0);
    shape->scale(12.0);

    delete shape;
  }
  catch (std::invalid_argument& error)
  {
    delete shape;
    std::cerr << "Something went wrong!";
    return 1;
  }

  return 0;
}
