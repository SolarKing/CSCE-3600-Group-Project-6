
/**
 * TODO:
 * [ ] print the parameters read
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <cctype> 

// try to avoid using namespace std


int main(int argc, char const *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    // std::cout << argv[i] << std::endl;

    if (argv[i] == std::string("-sizeL1"))
    {
      if (!std::isdigit(argv[++i][0]))
      {
        std::cout << "Error: Not a valid argument" << std::endl;
        return 1;
      }
      std::cout << "SizeL1 " << argv[i] << std::endl;
      // std::cout << "debug: entered into argument -sizeL1 condition" << std::endl;
    }

    if (argv[i] == std::string("-sizeL2")) 
    {
      if (!std::isdigit(argv[++i][0]))
      {
        std::cout << "Error: Not a valid argument" << std::endl;
        return 1;
      }
      std::cout << "SizeL2 " << argv[i] << std::endl;
      // std::cout << "debug: entered into argument -sizeL2 condition" << std::endl;
    }

    if (argv[i] == std::string("-type")) // direct or full
    {
      if ((argv[++i] == std::string("direct")))
      {
        std::cout << "Type Direct" << std::endl;
      }
      else if ((argv[++i] == std::string("full")))
      {
        std::cout << "Type Full" << std::endl;
      }
      else
      {
        std::cout << "Error: Not a valid argument" << std::endl;
        return 1;
      }

      // std::cout << "debug: entered into argument -type condition" << std::endl;
    }

    if (argv[i] == std::string("-write-policy")) // through or back
    {
       if ((argv[++i] == std::string("through")))
      {
        std::cout << "Write-Policy Through" << std::endl;
      }
      else if ((argv[++i] == std::string("back")))
      {
        std::cout << "Write-Policy Back" << std::endl;
      }
      else
      {
        std::cout << "Error: Not a valid argument" << std::endl;
        return 1;
      }
      // std::cout << "debug: entered into argument -write-policy condition" << std::endl;
    }
  }

  int x;
  std::string y;

  int totalRef = 0;
  int reads = 0;
  int writes = 0;

  while (std::cin >> x >> y) // by the RIGHT epstein
  {
    if (x == 0) 
    {
      totalRef ++;
      reads++;
    }
    else if (x == 1)
    {
      totalRef++;
      writes++;
    }
    else
    {
      std::cout << "Error: Something went wrong!" << std::endl;
      return 1;
    }
    // std::cout << "debug: The x is " << x << " and y is " << y << std::endl;
  }

  std::cout << totalRef << " Total" << std::endl;
  std::cout << reads << " Reads" << std::endl;
  std::cout << writes << " Writes" << std::endl;

  return 0;
}
