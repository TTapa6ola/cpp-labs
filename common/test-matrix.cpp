#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

const double accuracy = 10e-7;

BOOST_AUTO_TEST_SUITE(constructor_with_composite_shape_parameter)
BOOST_AUTO_TEST_CASE(correct_adding_shapes)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({2.0, 2.0}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    size_t expected_rows = 2;
    size_t expected_columns = 1;

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix(composite_shape);

    BOOST_CHECK_EQUAL(matrix.getRows(), expected_rows);
    BOOST_CHECK_EQUAL(matrix.getColumns(), expected_columns);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(correct_pushing_shapes)
  BOOST_AUTO_TEST_CASE(pushing_shapes_in_one_lay)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({150.0, 150.0}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    size_t expected_rows = 1;
    size_t expected_columns = 2;

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix;

    matrix.addShape(composite_shape[0]);
    matrix.addShape(composite_shape[1]);

    BOOST_CHECK_EQUAL(matrix.getRows(), expected_rows);
    BOOST_CHECK_EQUAL(matrix.getColumns(), expected_columns);
  }

  BOOST_AUTO_TEST_CASE(pushing_shapes_in_many_layers)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({2.0, 2.0}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    size_t expected_rows = 2;
    size_t expected_columns = 1;

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix;

    matrix.addShape(composite_shape[1]);
    matrix.addShape(composite_shape[0]);

    BOOST_CHECK_EQUAL(matrix.getRows(), expected_rows);
    BOOST_CHECK_EQUAL(matrix.getColumns(), expected_columns);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(handling_incorrect_parameters)
  BOOST_AUTO_TEST_CASE(handle_nullptr_in_add_shape)
  {
    afanasiev::Matrix matrix;
    BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_index_out_of_rows)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({2.0, 2.0}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix;

    BOOST_CHECK_THROW(matrix[45][0], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_index_out_of_columns)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({2.0, 2.0}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::Matrix matrix;

    BOOST_CHECK_THROW(matrix[0][42], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_empty_matrix_in_operator_of_indexation)
  {
    afanasiev::Matrix matrix;

    BOOST_CHECK_THROW(matrix[0][0], std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
