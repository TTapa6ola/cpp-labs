#ifndef A4_MATRIX_HPP
#define A4_MATRIX_HPP
#include "shape.hpp"
#include "composite-shape.hpp"

namespace afanasiev
{
  class Matrix
  {
  public:
    class Layer
    {
    public:
      const Shape::ShapePointer operator[] (size_t index) const;

    private:
      Shape::ShapePointer* layer_;
      size_t size_;
      Layer(Shape::ShapePointer& layer, size_t size);
      friend class Matrix;
    };
    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    Matrix(const CompositeShape& composite_shape);
    ~Matrix() = default;
    const Matrix& operator=(const Matrix& matrix);
    const Matrix& operator=(Matrix&& matrix) noexcept;
    size_t getRows() const;
    size_t getColumns() const;
    Layer operator[] (size_t index) const;
    void addShape(const Shape::ShapePointer& shape);
    size_t findRowIndex(const Shape::ShapePointer& shape) const;
    size_t findColumnIndex(size_t row) const;

  private:
    size_t rows_;
    size_t columns_;
    Shape::ShapeArray matrix_;
    void extendRows();
    void extendColumns();
  };
}

#endif //A4_MATRIX_HPP
