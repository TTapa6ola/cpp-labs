#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

const double accuracy = 10e-7;

BOOST_AUTO_TEST_SUITE(method_move)
  BOOST_AUTO_TEST_CASE(correct_moving_composite_shape_by_point)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::point_t expectedCenter = composite_shape.getCenter();
    double expectedArea = composite_shape.getArea();

    expectedCenter.x = 1.2;
    expectedCenter.y = 3.4;

    composite_shape.move({1.2, 3.4});

    BOOST_CHECK_CLOSE(composite_shape.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().y, expectedCenter.y, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_moving_composite_shape_by_double)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::point_t expectedCenter = composite_shape.getCenter();
    double expectedArea = composite_shape.getArea();

    expectedCenter.x += 1.2;
    expectedCenter.y += 3.4;

    composite_shape.move(1.2, 3.4);

    BOOST_CHECK_CLOSE(composite_shape.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().y, expectedCenter.y, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_scale)
  BOOST_AUTO_TEST_CASE(correct_square_after_scaling_composite_shape)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double coefficient = 2.0;
    double expectedArea = coefficient * coefficient * composite_shape.getArea();

    composite_shape.scale(coefficient);

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_scale)
  BOOST_AUTO_TEST_CASE(correct_square_after_scaling_composite_shape_with_1)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double coefficient = 1.0;
    double expectedArea = coefficient * coefficient * composite_shape.getArea();

    composite_shape.scale(coefficient);

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_rotate)
  BOOST_AUTO_TEST_CASE(correct_unchanged_center_after_rotation)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    afanasiev::point_t center = composite_shape.getCenter();

    composite_shape.rotate(90);

    BOOST_CHECK_CLOSE(composite_shape.getCenter().x, center.x, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getCenter().y, center.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_unchanged_area_after_rotation)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double expectedArea = composite_shape.getArea();

    composite_shape.rotate(20);

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_width_and_height_after_rotation)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({-2.0, -2.0}, 2.0);
    afanasiev::Rectangle rectangle(2.0, 1.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double expected_width = composite_shape.getFrameRect().height;
    double expected_height = composite_shape.getFrameRect().width;

    composite_shape.rotate(90);

    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().width, expected_width, accuracy);
    BOOST_CHECK_CLOSE(composite_shape.getFrameRect().height, expected_height, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operator_of_indexation)
  BOOST_AUTO_TEST_CASE(correct_handling_shapes)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double coefficient = 2.0;
    double expectedArea = composite_shape.getArea() - rectangle.getArea();
    size_t expectedSize = composite_shape.getSize();

    composite_shape[1]->scale(coefficient);
    expectedArea += composite_shape[1]->getArea();

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
    BOOST_CHECK_EQUAL(composite_shape.getSize(), expectedSize);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_get_frame_rect)
BOOST_AUTO_TEST_CASE(handle_method_get_frame_rect_with_empty_composite_shapes)
  {
    afanasiev::CompositeShape composite_shape, composite_shape1, composite_shape2;
    afanasiev::Circle circle({0.0, 0.0}, 0.0);
    double expectedArea = circle.getArea();

    composite_shape.pushBack(std::make_shared<afanasiev::CompositeShape>(composite_shape1));
    composite_shape.pushBack(std::make_shared<afanasiev::CompositeShape>(composite_shape2));
    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_push_back)
  BOOST_AUTO_TEST_CASE(correct_pushing_shape_back)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double expectedArea = composite_shape.getArea();
    size_t expectedSize = composite_shape.getSize();

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));

    expectedArea += circle.getArea();
    expectedSize++;

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
    BOOST_CHECK_EQUAL(composite_shape.getSize(), expectedSize);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_delete_shape)
  BOOST_AUTO_TEST_CASE(correct_delete_shape)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    double expectedArea = composite_shape.getArea();
    size_t expectedSize = composite_shape.getSize();

    composite_shape.deleteShape(1);

    expectedArea -= rectangle.getArea();
    expectedSize--;

    BOOST_CHECK_CLOSE(composite_shape.getArea(), expectedArea, accuracy);
    BOOST_CHECK_EQUAL(composite_shape.getSize(), expectedSize);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(handling_incorrect_parameters)
  BOOST_AUTO_TEST_CASE(handle_negative_parameter_in_scaling_composite_shape)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    BOOST_CHECK_THROW(composite_shape.scale(-42.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_nullptr_in_method_pushback)
  {
    afanasiev::CompositeShape composite_shape;
    BOOST_CHECK_THROW(composite_shape.pushBack(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_negative_parameter_in_operator_of_indexation)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    BOOST_CHECK_THROW(composite_shape[-42], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_index_more_than_size_in_method_delete_shape)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    composite_shape.pushBack(std::make_shared<afanasiev::Circle>(circle));
    composite_shape.pushBack(std::make_shared<afanasiev::Rectangle>(rectangle));

    BOOST_CHECK_THROW(composite_shape.deleteShape(42), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(calling_methods_on_empty_array)
  BOOST_AUTO_TEST_CASE(calling_get_frame_rect_on_empty_array)
  {
    afanasiev::CompositeShape composite_shape;
    afanasiev::rectangle_t rectangle = composite_shape.getFrameRect();
    BOOST_CHECK_CLOSE(rectangle.width, -1.0, accuracy);
    BOOST_CHECK_CLOSE(rectangle.height, -1.0, accuracy);
    BOOST_CHECK_CLOSE(rectangle.pos.x, 0.0, accuracy);
    BOOST_CHECK_CLOSE(rectangle.pos.y, 0.0, accuracy);
  }

  BOOST_AUTO_TEST_CASE(calling_delete_shape_on_empty_array)
  {
    afanasiev::CompositeShape composite_shape;
    BOOST_CHECK_THROW(composite_shape.deleteShape(0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
