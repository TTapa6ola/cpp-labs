#include "tasks.hpp"
#include <set>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "shape.hpp"

int tasks::task1()
{
  std::set<std::string> words((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  return 0;
}

int tasks::task2()
{
  std::list<detail::Shape> shapes{std::istream_iterator<detail::Shape>(std::cin), std::istream_iterator<detail::Shape>()};

  if (!std::cin.eof())
  {
    if (detail::errors.empty())
    {
      throw std::runtime_error("Reading data error");
    }
    std::string data;
    std::ios_base::iostate state(std::cin.rdstate());
    std::cin.clear();
    std::getline(std::cin >> std::ws, data);
    std::cin.setstate(state);
    std::string error = "Error is found: '" + data + "':\n";
    for (std::string i : detail::errors)
    {
      error += "-> " + i + '\n';
    }
    throw std::invalid_argument(error);
  }

  size_t count_vertices = 0;
  size_t count_triangles = 0;
  size_t count_squares = 0;
  size_t count_rectangles = 0;

  std::for_each(shapes.begin(), shapes.end(), [&](const detail::Shape& shape)
  {
      count_vertices += shape.size();
      if (shape.size() == 3)
      {
        count_triangles++;
      }

      if (shape.size() == 4)
      {
        if (detail::is_rect(shape))
        {
          count_rectangles++;
          if (detail::is_square(shape))
          {
            count_squares++;
          }
        }
      }
  });

  shapes.remove_if([](const detail::Shape& shape)
  {
      return shape.size() == 5;
  });

  std::vector<detail::Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const detail::Shape& shape)
  {
      return shape[0];
  });

  shapes.sort(detail::comparator);

  std::cout << "Vertices: " << count_vertices << '\n';
  std::cout << "Triangles: " << count_triangles << '\n';
  std::cout << "Squares: " << count_squares << '\n';
  std::cout << "Rectangles: " << count_rectangles << '\n';
  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<detail::Point>(std::cout, " "));
  std::cout << "\nShapes: \n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<detail::Shape>(std::cout, "\n"));

  return 0;
}
