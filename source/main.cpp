
/**
 * TODO:
 * [ ] handle arguments into program flow
 */

#include <iostream>
#include <cstdlib>
#include <string>

// try to avoid using namespace std

int main(int argc, char const *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    std::cout << argv[i] << std::endl;
    if (argv[i] == std::string("-sizeL1"))
    {
      std::cout << "debug: entered into argument -sizeL1 condition" << std::endl;
    }
    else if (argv[i] == std::string("-sizeL2")) 
    {
      std::cout << "debug: entered into argument -sizeL2 condition" << std::endl;
    }
    else if (argv[i] == std::string("-type"))
    {
      std::cout << "debug: entered into argument -type condition" << std::endl;
    }
    else if (argv[i] == std::string("-write-policy"))
    {
      std::cout << "debug: entered into argument -write-policy condition" << std::endl;
    }
  }
  return 0;
}
