////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include "App.hpp"

#include <iostream>
#include <stdexcept>

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
    return -1;
  }
  
  return 0;
}
