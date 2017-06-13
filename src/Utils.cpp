////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "Utils.hpp"

#include <iostream>
#include <stdexcept>

////////////////////////////////////////////////////////////
int getFromInput(const std::string& message)
{
  std::string input;
  int number;

  do
  {
    std::cout << message << ": ";
    std::getline(std::cin, input);

    try
    {
      number = std::stoi(input);
    }
    catch (const std::invalid_argument& err)
    {
      continue;
    }
    catch (const std::out_of_range& err)
    {
      continue;
    }
    
  }
  while (input.empty());

  return number;
}


////////////////////////////////////////////////////////////
std::string getStringFromInput(const std::string& message)
{
  std::string input;

  do
  {
    std::cout << message << ": ";
    std::getline(std::cin, input);
  }
  while (input.empty());

  return input;
}
