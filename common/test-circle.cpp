#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

const double accuracy = 10e-7;

BOOST_AUTO_TEST_SUITE(method_move)
  BOOST_AUTO_TEST_CASE(correct_moving_circle_by_point)
  {
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::rectangle_t expectedCircle = circle.getFrameRect();
    afanasiev::point_t expectedFrameCenter = expectedCircle.pos;
    afanasiev::point_t expectedCenter = circle.getCenter();
    double expectedArea = circle.getArea();

    expectedFrameCenter.x = 4.2;
    expectedFrameCenter.y = 6.9;
    expectedCenter.x = 4.2;
    expectedCenter.y = 6.9;

    circle.move({4.2, 6.9});

    BOOST_CHECK_EQUAL(circle.getFrameRect().height, expectedCircle.height);
    BOOST_CHECK_EQUAL(circle.getFrameRect().width, expectedCircle.width);
    BOOST_CHECK_EQUAL(circle.getArea(), expectedArea);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, expectedFrameCenter.x, accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, expectedFrameCenter.y, accuracy);
    BOOST_CHECK_CLOSE(circle.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(circle.getCenter().y, expectedCenter.y, accuracy);
  }

  BOOST_AUTO_TEST_CASE(correct_moving_circle_by_double)
  {
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    afanasiev::rectangle_t expectedCircle = circle.getFrameRect();
    afanasiev::point_t expectedFrameCenter = expectedCircle.pos;
    afanasiev::point_t expectedCenter = circle.getCenter();
    double expectedArea = circle.getArea();

    expectedFrameCenter.x += 4.2;
    expectedFrameCenter.y += 6.9;
    expectedCenter.x += 4.2;
    expectedCenter.y += 6.9;

    circle.move(4.2, 6.9);

    BOOST_CHECK_EQUAL(circle.getFrameRect().height, expectedCircle.height);
    BOOST_CHECK_EQUAL(circle.getFrameRect().width, expectedCircle.width);
    BOOST_CHECK_EQUAL(circle.getArea(), expectedArea);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, expectedFrameCenter.x, accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, expectedFrameCenter.y, accuracy);
    BOOST_CHECK_CLOSE(circle.getCenter().x, expectedCenter.x, accuracy);
    BOOST_CHECK_CLOSE(circle.getCenter().y, expectedCenter.y, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(method_scale)
  BOOST_AUTO_TEST_CASE(correct_square_after_scaling_circle)
  {
    afanasiev::Circle circle({1.0, 2.4}, 8.8005553535);
    double coefficient = 3.1415926535;
    double expectedArea = coefficient * coefficient * circle.getArea();

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getArea(), expectedArea, accuracy);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(handling_incorrect_parameters)
  BOOST_AUTO_TEST_CASE(handle_negative_parameters_in_circle_constructor)
  {
    BOOST_CHECK_THROW(afanasiev::Circle({2.0, 3.3}, -4.3), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(handle_negative_parameter_in_scaling_circle)
  {
    afanasiev::Circle circle({1.0, 2.4}, 3.0);
    BOOST_CHECK_THROW(circle.scale(-42.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
