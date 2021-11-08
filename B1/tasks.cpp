#include "tasks.hpp"
#include <stdexcept>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include "detail.hpp"


bool tasks::choose_order(const char* order)
{
  if ((std::strcmp(order, "ascending") == 0) || (std::strcmp(order, "descending") == 0))
  {
    return std::strcmp(order, "ascending") == 0;
  }
  else
  {
    throw std::invalid_argument("Wrong parameter of sorting direction");
  }
}

void tasks::first_task(const char* order)
{
  std::vector<int> vector;
  std::vector<int> vector_at;
  std::list<int> list;
  bool sort_order = choose_order(order);
  int number = 0;

  while (std::cin >> number)
  {
    vector.push_back(number);
    vector_at.push_back(number);
    list.push_back(number);
  }

  if (!std::cin.eof() && std::cin.bad())
  {
    throw std::runtime_error("Something went wrong while reading file");
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Entered is not an integer");
  }

  if (vector.empty())
  {
    return;
  }

  detail::sort<detail::IndexOperator<std::vector<int>>, std::vector<int>>(vector, sort_order);
  detail::print(vector);
  detail::sort<detail::MethodAt<std::vector<int>>, std::vector<int>>(vector_at, sort_order);
  detail::print(vector_at);
  detail::sort<detail::Iterator<std::list<int>>, std::list<int>>(list, sort_order);
  detail::print(list);
}

void tasks::second_task(const char* file)
{
  std::ifstream input_file(file);

  if (!input_file.is_open())
  {
    throw std::invalid_argument("File did not open correctly");
  }

  int step = 8;
  int counter = 0;
  std::unique_ptr<char[]> array = std::make_unique<char[]>(step);
  char symbol;

  input_file >> std::noskipws;
  while (input_file >> symbol)
  {
    if (counter == step)
    {
      std::unique_ptr<char[]> new_array = std::make_unique<char[]>(step * 2);
      for (int i = 0; i < counter; i++)
      {
        new_array[i] = array[i];
      }

      new_array[counter] = symbol;
      counter++;
      step *= 2;
      std::swap(array, new_array);
    }
    else
    {
      array[counter] = symbol;
      counter++;
    }
  }

  if (!input_file.eof() && input_file.bad())
  {
    throw std::runtime_error("Something went wrong while reading from the file");
  }

  std::vector<char> vector (&array[0], &array[counter]);

  for (char el : vector)
  {
    std::cout << el;
  }
}

void tasks::third_task()
{
  std::vector<int> vector;
  int number;

  while ((std::cin >> number) && (number != 0))
  {
    vector.push_back(number);
  }

  if (!std::cin.eof() && std::cin.bad())
  {
    throw std::runtime_error("Something went wrong while reading file");
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::invalid_argument("Entered is not an integer");
  }

  if (vector.empty())
  {
    return;
  }

  if (number != 0)
  {
    throw std::invalid_argument("The end of the sequence must be zero");
  }

  if (vector.back() == 1)
  {
    std::vector<int>::iterator it = vector.begin();
    while (it != vector.end())
    {
      if (*it % 2 == 0)
      {
        it = vector.erase(it);
      }
      else
      {
        it++;
      }
    }
  }

  if (vector.back() == 2)
  {
    std::vector<int>::iterator it = vector.begin();

    while (it != vector.end())
    {
      if (*it % 3 == 0)
      {
        it = vector.insert(++it, 3, 1);
        it += 2;
      }
      it++;
    }
  }

  detail::print(vector);
}

void tasks::fourth_task(const char* order, int size)
{
  std::vector<double> vector(size);
  detail::fillRandom(&vector[0], size);
  detail::print(vector);
  detail::sort<detail::IndexOperator<std::vector<double>>, std::vector<double>> (vector, choose_order(order));
  detail::print(vector);
}
