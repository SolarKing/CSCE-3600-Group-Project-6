
#include "parse.h"
#include "part2.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>

int main(int argc, char const *argv[])
{
  Parse traceFile; // this will handle the tracefile

  // storage for the trace file into "main memory"

  int x; // for read/write
  int y; // for the hex value

  // traceFile.getArguments(argc, argv);

  int cacheSize = 0; // size of the cache 

  if (argc > 1)
  {
    std::cout << "Input Parameters read:" << std::endl;
  }
  else
  {
    std::cout << "No input parameters were read..." << std::endl;
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
      std::cout << "SizeL1 " << argv[i] << std::endl;
      cacheSize = std::stoi(argv[i]);


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
      std::cout << "SizeL2 " << argv[i] << std::endl;

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
        std::cout << "Type Direct" << std::endl;
        i++;
      }
      else if ((argv[i+1] == std::string("full")))
      {
        std::cout << "Type Full" << std::endl;
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
        std::cout << "Write-Policy Through" << std::endl;
        i++;
      }
      else if ((argv[i+1] == std::string("back")))
      {
        std::cout << "Write-Policy Back" << std::endl;
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

  ////////////////////////////
  // PARSING / PROGRAM FLOW //
  ////////////////////////////

  int numOfHits = 0;
  int numOfMisses = 0;

  std::string tagValue;

  // int cacheSize = 32768;
  // int cacheSize = 16384;
  int cacheLines = findCacheLines(cacheSize, ADDR_SIZE);
  int bitBlockSize = findBitBlockSize(cacheLines);
  int tagSize = findTagSize(ADDR_SIZE, bitBlockSize, OFFSET);

  std::string *tagArray = new std::string[cacheLines];
  initStringArray(tagArray, cacheLines, "null");

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << tagArray[i] << std::endl;
  // }

  bool *validArray = new bool[cacheLines];
  initBoolArray(validArray,  cacheLines, false);

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << validArray[i] << std::endl;
  // }
  // 
  
  int loadCounter = 0;

  std::cout << "Loading" << std::flush;

  while (std::cin >> x) // credit to epstein
  {

    // loading animation
    if (loadCounter % 100000 == 25000)
    {
      std::cout << "." << std::flush;
    }
    else if (loadCounter % 100000 == 50000)
    {
      std::cout << "." << std::flush;
    }
    else if (loadCounter % 100000 == 75000)
    {
      std::cout << "\b\b\b   \b\b\b" << std::flush;
    }
    else if (loadCounter % 100000 == 0)
    {
      std::cout << "." << std::flush;
    }
    loadCounter++;



    // std::cout << "Cache Lines: " << cacheLines << std::endl;
    std::cin >> std::hex >> y;
    // std::cout << "Hex Value:" << std::hex << y << std::endl;
    // std::cout << "Decimal Value: " << std::dec << y << std::endl;
    // std::cout << "Binary Value: " << std::bitset<ADDR_SIZE>(y).to_string() << std::endl;
    
    tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSize);
    // std::cout << "The LinePos is " << getLinePos(y, cacheLines) << std::endl;
    // std::cout << "Tag Size: " << tagSize << std::endl;
    // std::cout << "Tag Value: " << tagValue << std::endl << std::endl;


    if (x == 1) 
    {
      traceFile.addARead();
      if (tagArray[getLinePos(y, cacheLines)] == tagValue)
      {
        numOfHits++;
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << tagArray[getLinePos(y, cacheLines)] << "==" << tagValue << std::endl;
        // std::cout << "HIT!" << std::endl;
      }
      else
      {
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << tagArray[getLinePos(y, cacheLines)] << "!=" << tagValue << std::endl;
        tagArray[getLinePos(y, cacheLines)] = tagValue;
        numOfMisses++;
        // std::cout << "MISS!" << std::endl;
      }

    }
    else if (x == 0)
    {

      traceFile.addAWrite();
      if (tagArray[getLinePos(y, cacheLines)] == tagValue)
      {
        numOfHits++;
        validArray[getLinePos(y, cacheLines)] = true;
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << tagArray[getLinePos(y, cacheLines)] << "==" << tagValue << std::endl;
        // std::cout << "HIT!" << std::endl;
      }
      else
      {
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << tagArray[getLinePos(y, cacheLines)] << "!=" << tagValue << std::endl;
        tagArray[getLinePos(y, cacheLines)] = tagValue;
        numOfMisses++;
        // std::cout << "MISS!" << std::endl;
      }
    }
    else
    {
      std::cout << "Error: Something went wrong when reading the trace file" << std::endl;
      std::cout << "Exiting Program..." << std::endl;
      return 1;
    }

    // std::cout << "debug: The x is " << x << " and y is " << y << std::endl;
  }
  std::cout << "\b\b\b\b\b\b\b\b\b\bLoading Done!" << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << "Memory refreneces read from file:" << std::endl;
  std::cout << traceFile.getTotal() << " Total" << std::endl;
  std::cout << traceFile.getNumOfReads() << " Reads" << std::endl;
  std::cout << traceFile.getNumOfWrites() << " Writes" << std::endl;

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << tagArray[i] << " " << validArray[i] << std::endl;
  // }

  // std::cout << "  Hits: " << numOfHits << std::endl;
  // std::cout << "Misses: " << numOfMisses << std::endl << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << "  Hits: " << getPercentage(numOfHits, numOfHits+numOfMisses) << " \%" <<std::endl;
  std::cout << "Misses: " << getPercentage(numOfMisses, numOfHits+numOfMisses) <<  " \%" << std::endl << std::endl;
 
  return 0;
}
