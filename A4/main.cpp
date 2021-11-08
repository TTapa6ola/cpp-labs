#include <iostream>
#include <stdexcept>
#include <memory>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({2.0, 3.0}, 7.0);
    afanasiev::Rectangle rectangle(1.0, 2.0, {4.0, 3.2});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix(composite_shape);

    matrix.getRows();
    matrix.getColumns();

    for(size_t i = 0; i < composite_shape.getSize(); i++)
    {
      composite_shape[i]->getArea();
      composite_shape[i]->getFrameRect();
      composite_shape[i]->getCenter();
      composite_shape[i]->move({-1.0, -2.0});
      composite_shape[i]->move(2.0, 1.0);
      composite_shape[i]->scale(12.0);
      composite_shape[i]->rotate(30.0);
    }

    composite_shape.getArea();
    composite_shape.getFrameRect();
    composite_shape.getCenter();
    composite_shape.move({-1.0, -2.0});
    composite_shape.move(2.0, 1.0);
    composite_shape.scale(12.0);
    composite_shape.rotate(30.0);

    composite_shape.deleteShape(0);
    composite_shape.deleteShape(0);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << "Something went wrong!";
    return 1;
  }

  return 0;
}
