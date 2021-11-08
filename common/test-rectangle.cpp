#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"
#include "rectangle.hpp"

const double accuracy = 10e-7;

BOOST_AUTO_TEST_SUITE(method_move)
  BOOST_AUTO_TEST_CASE(correct_moving_rectangle_by_point)
  {
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    afanasiev::rectangle_t expectedRectangle = rectangle.getFrameRect();
    afanasiev::point_t expectedFrameCenter = expectedRectangle.pos;
    afanasiev::point_t expectedCenter = rectangle.getCenter();
    double expectedArea = rectangle.getArea();

    expectedFrameCenter.x = -1.0;
    expectedFrameCenter.y = 1.0;
    expectedCenter.x = -1.0;
    expectedCenter.y = 1.0;

    rectangle.move({-1.0, 1.0});

    BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, expectedRectangle.height);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, expectedRectangle.width);
    BOOST_CHECK_EQUAL(rectangle.getArea(), expectedArea);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, expectedFrameCenter.x, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, expectedFrameCenter.y, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, expectedCenter.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_moving_rectangle_by_double)
  {
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    afanasiev::rectangle_t expectedRectangle = rectangle.getFrameRect();
    afanasiev::point_t expectedFrameCenter = expectedRectangle.pos;
    afanasiev::point_t expectedCenter = rectangle.getCenter();
    double expectedArea = rectangle.getArea();

    expectedFrameCenter.x += -1.0;
    expectedFrameCenter.y += 1.0;
    expectedCenter.x += -1.0;
    expectedCenter.y += 1.0;
    rectangle.move(-1.0, 1.0);

    BOOST_CHECK_EQUAL(rectangle.getFrameRect().height, expectedRectangle.height);
    BOOST_CHECK_EQUAL(rectangle.getFrameRect().width, expectedRectangle.width);
    BOOST_CHECK_EQUAL(rectangle.getArea(), expectedArea);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, expectedFrameCenter.x, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, expectedFrameCenter.y, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, expectedCenter.y, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_scale)
  BOOST_AUTO_TEST_CASE(correct_square_after_scaling_rectangle)
  {
    afanasiev::Rectangle rectangle(1.41421356, 1.73205080, {2.0, 2.0});
    double coefficient = 2.71828182;
    double expectedArea = coefficient * coefficient * rectangle.getArea();

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_rotate)
  BOOST_AUTO_TEST_CASE(correct_unchanged_center_after_rotation_of_rectangle)
  {
    afanasiev::point_t center{2.0, 2.0};
    afanasiev::Rectangle rectangle(1.41421356, 1.73205080, center);

    rectangle.rotate(30);

    BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_unchanged_area_after_rotation_of_rectangle)
  {
    afanasiev::Rectangle rectangle(1.41421356, 1.73205080, {2.0, 2.0});
    double expectedArea = rectangle.getArea();

    rectangle.rotate(30);

    BOOST_CHECK_CLOSE(rectangle.getArea(), expectedArea, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_width_and_height_after_rectangle_rotation)
  {
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    double expected_width = rectangle.getFrameRect().height * sin(M_PI / 3);
    double expected_height = rectangle.getFrameRect().width * sin(M_PI / 3);

    rectangle.rotate(60);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, expected_width, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, expected_height, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_width_and_height_after_rectangle_rotation_on_90_degrees)
  {
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});

    double expected_width = rectangle.getFrameRect().height * sin(M_PI / 2);
    double expected_height = rectangle.getFrameRect().width * sin(M_PI / 2);

    rectangle.rotate(90);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, expected_width, accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, expected_height, accuracy);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(handling_incorrect_parameters)
  BOOST_AUTO_TEST_CASE(handle_negative_parameters_in_rectangle_constructor)
  {
    BOOST_CHECK_THROW(afanasiev::Rectangle(-2.0, 2.0, {1.1, 2.2}), std::invalid_argument);
    BOOST_CHECK_THROW(afanasiev::Rectangle(2.0, -2.0, {1.1, 2.2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_negative_parameter_in_scaling_rectangle)
  {
    afanasiev::Rectangle rectangle(3.0, 4.0, {2.0, 2.0});
    BOOST_CHECK_THROW(rectangle.scale(-42.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
