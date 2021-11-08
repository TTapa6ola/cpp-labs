#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace afanasiev
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& composite_shape);
    CompositeShape(CompositeShape&& composite_shape) noexcept;
    ~CompositeShape() = default;
    CompositeShape& operator=(const CompositeShape& composite_shape);
    CompositeShape& operator=(CompositeShape&& composite_shape) noexcept;
    const ShapePointer operator[] (size_t index) const;
    double getArea() const override;
    size_t getSize() const;
    point_t getCenter() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double x, double y) override;
    void scale(double coefficient) override;
    void rotate(double angle) override;
    void pushBack(const ShapePointer shape);
    void deleteShape(size_t index);

  private:
    size_t size_;
    ShapeArray array_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP
