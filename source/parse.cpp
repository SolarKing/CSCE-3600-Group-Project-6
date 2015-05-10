#include "parse.h"

// constructor
Parse::Parse()
{
  nTotal = 0;
  nReads = 0;
  nWrites = 0;
}

int Parse::getTotal()
{
  return nTotal;
}

int Parse::getNumOfReads()
{
  return nReads;
}

int Parse::getNumOfWrites()
{
  return nWrites;
}

int Parse::addARead()
{
  nTotal++;
  return ++nReads;
}

int Parse::addAWrite()
{
  nTotal++;
  return ++nWrites;
}

int Parse::getArguments(int argc, char const *argv[], int &cacheSizeL1, int &cacheSizeL2, std::string &replacementPolicy)
{
  std::cout << "=============================================================" << std::endl;
  if (argc > 1)
  {
    std::cout << "Input Parameters read:" << std::endl;
  }
  else
  {
    std::cout << "No input parameters were read..." << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    // std::cout << "debug: argument " << argv[i] << "entered." << std::endl;

    if (argv[i] == std::string("-sizeL1"))
    {
      // handle if there is no argument after -sizeL1
      if (i+1 >= argc)
      {
        std::cout << "Error: Missing argument after \"-sizeL1\"" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // handle if the argument after -sizeL1 is not an integer
      if (!std::isdigit(argv[++i][0]))
      {
        std::cout << "Error: Argument after \"-sizeL1\" is not a valid digit" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // expected output from entering "-sizeL1 xx" arguments
      std::cout << "  SizeL1 " << argv[i] << std::endl;
      cacheSizeL1 = std::atoi(argv[i]);


      // std::cout << "debug: entered into argument -sizeL1 condition" << std::endl;
    }

    if (argv[i] == std::string("-sizeL2")) 
    {
      // handle if there is no argument after -sizeL2
      if (i+1 >= argc)
      {
        std::cout << "Error: Missing argument after \"-sizeL2\"" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // handle if the argument after -sizeL2 is not an integer
      if (!std::isdigit(argv[++i][0]))
      {
        std::cout << "Error: Argument after \"-sizeL2\" is not a valid digit" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // print expected output from entering "-sizeL2 xx" arguments
      std::cout << "  SizeL2 " << argv[i] << std::endl;
      cacheSizeL2 = std::atoi(argv[i]);

      // std::cout << "debug: entered into argument -sizeL2 condition" << std::endl;
    }

    if (argv[i] == std::string("-type")) // direct or full
    {
      // handle if there is no argument after -type
      if (i+1 >= argc)
      {
        std::cout << "Error: Missing argument after \"-type\"" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // handle if there is a valid command entered after -type
      if ((argv[i+1] == std::string("direct")))
      {
        std::cout << "  Type Direct" << std::endl;
        replacementPolicy = "direct";
        i++;
      }
      else if ((argv[i+1] == std::string("full")))
      {
        std::cout << "  Type Full" << std::endl;
        replacementPolicy = "full";
        i++;
      }
      else
      {
        std::cout << "Error: Argument after \"-type\" is not a valid command" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // std::cout << "debug: entered into argument -type condition" << std::endl;
    }

    if (argv[i] == std::string("-write-policy")) // through or back
    {
      // handle if there is no argument after -write-policy
      if (i+1 >= argc)
      {
        std::cout << "Error: Missing argument after \"-write-policy\"" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // handle if there is a valid command entered after -type
      if ((argv[i+1] == std::string("through")))
      {
        std::cout << "  Write-Policy Through" << std::endl;
        i++;
      }
      else if ((argv[i+1] == std::string("back")))
      {
        std::cout << "  Write-Policy Back" << std::endl;
        i++;
      }
      else
      {
        std::cout << "Error: Argument after \"-write-policy\" is not a valid command" << std::endl;
        std::cout << "Exiting Program..." << std::endl;
        return 1;
      }

      // std::cout << "debug: entered into argument -write-policy condition" << std::endl;
    }
  }
  return 0;
}
