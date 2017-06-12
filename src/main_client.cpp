////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "App.hpp"

#include <stdexcept>
#include <iostream>

////////////////////////////////////////////////////////////
int main()
{
  try
  {
    App app;
    app.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}