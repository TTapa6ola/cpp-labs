#include "matrix.hpp"

afanasiev::Matrix::Layer::Layer(Shape::ShapePointer& layer, size_t size):
  layer_(&layer),
  size_(size)
{
  if (!layer)
  {
    throw std::invalid_argument("Invalid matrix, it can`t be nullptr");
  }
}

const afanasiev::Shape::ShapePointer afanasiev::Matrix::Layer::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::invalid_argument("Index out of array");
  }

  return layer_[index];
}

afanasiev::Matrix::Matrix():
  rows_(0),
  columns_(0),
  matrix_(nullptr)
{}

afanasiev::Matrix::Matrix(const afanasiev::Matrix& matrix):
  rows_(matrix.rows_),
  columns_(matrix.columns_),
  matrix_(std::make_unique<Shape::ShapePointer[]>(rows_ * columns_))
{
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    matrix_[i] = matrix.matrix_[i];
  }
}

afanasiev::Matrix::Matrix(afanasiev::Matrix&& matrix) noexcept:
  rows_(matrix.rows_),
  columns_(matrix.columns_),
  matrix_(std::move(matrix.matrix_))
{
  matrix.rows_ = 0;
  matrix.columns_ = 0;
}

afanasiev::Matrix::Matrix(const CompositeShape& composite_shape):
  rows_(0),
  columns_(0),
  matrix_(nullptr)
{
  for (size_t i = 0; i < composite_shape.getSize(); i++)
  {
    addShape(composite_shape[i]);
  }
}

const afanasiev::Matrix& afanasiev::Matrix::operator=(const afanasiev::Matrix& matrix)
{
  if (this == &matrix)
  {
    return *this;
  }

  Shape::ShapeArray new_matrix(std::make_unique<Shape::ShapePointer[]>(matrix.rows_ * matrix.columns_));

  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    new_matrix[i] = matrix.matrix_[i];
  }

  matrix_.swap(new_matrix);

  rows_ = matrix.rows_;
  columns_ = matrix.columns_;

  return *this;
}

const afanasiev::Matrix& afanasiev::Matrix::operator=(afanasiev::Matrix&& matrix) noexcept
{
  if (this == &matrix)
  {
    return *this;
  }

  rows_ = matrix.rows_;
  columns_ = matrix.columns_;
  matrix_ = std::move(matrix.matrix_);

  matrix.rows_ = 0;
  matrix.columns_ = 0;

  return *this;
}

size_t afanasiev::Matrix::getRows() const
{
  return rows_;
}

size_t afanasiev::Matrix::getColumns() const
{
  return columns_;
}

afanasiev::Matrix::Layer afanasiev::Matrix::operator[](size_t index) const
{
  if (index >= rows_)
  {
    throw std::invalid_argument("Index out of array");
  }

  return Layer(matrix_[columns_ * index], columns_);
}

void afanasiev::Matrix::addShape(const afanasiev::Shape::ShapePointer& shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid shape, it can`t be nullptr");
  }

  size_t row_index = findRowIndex(shape);

  if (row_index == rows_)
  {
    extendRows();
  }

  size_t column_index = findColumnIndex(row_index);

  if (column_index == columns_)
  {
    extendColumns();
  }

  matrix_[row_index * columns_ + column_index] = shape;
}

size_t afanasiev::Matrix::findRowIndex(const afanasiev::Shape::ShapePointer& shape) const
{
  size_t row_index = 0;

  for (size_t r = 0; r < rows_; r++)
  {
    for (size_t c = 0; c < columns_; c++)
    {
      rectangle_t rectangle1 = shape->getFrameRect();
      rectangle_t rectangle2 = matrix_[r * columns_ + c]->getFrameRect();

      if (areRectanglesIntersected(rectangle1, rectangle2))
      {
        row_index++;
        break;
      }
    }
  }

  return row_index;
}

size_t afanasiev::Matrix::findColumnIndex(size_t row_index) const
{
  size_t column_index = 0;

  for (; column_index < columns_; column_index++)
  {
    if (matrix_[row_index * columns_ + column_index] == nullptr)
    {
      return column_index;
    }
  }

  return column_index;
}

void afanasiev::Matrix::extendRows()
{
  rows_++;
  Shape::ShapeArray matrix(std::make_unique<Shape::ShapePointer[]>(rows_ * columns_));

  for (size_t r = 0; r < rows_ - 1; r++)
  {
    for (size_t c = 0; c < columns_; c++)
    {
      matrix[r * columns_ + c] = matrix_[r * columns_ + c];
    }
  }

  matrix_ = std::move(matrix);
}

void afanasiev::Matrix::extendColumns()
{
  columns_++;
  Shape::ShapeArray matrix(std::make_unique<Shape::ShapePointer[]>(rows_ * columns_));

  for (size_t r = 0; r < rows_; r++)
  {
    for (size_t c = 0; c < columns_ - 1; c++)
    {
      matrix[r * columns_ + c] = matrix_[r * columns_ + c];
    }
  }

  matrix_ = std::move(matrix);
}
