#include "part3.h"

Cache::Cache(int cacheLines)
{
  *tagArray = new std::string[cacheLines];
  initStringArray(tagArray, cacheLines, "null");

  *validArray = new bool[cacheLines];
  initBoolArray(validArrayL1,  cacheLines, false);
}

void loadAnimation(int &loadCounter)
{
  // loading animation
  if (loadCounter % 400000 == 100000)
  {
    std::cout << "." << std::flush;
  }
  else if (loadCounter % 400000 == 200000)
  {
    std::cout << "." << std::flush;
  }
  else if (loadCounter % 400000 == 300000)
  {
    std::cout << "\b\b\b   \b\b\b" << std::flush;
  }
  else if (loadCounter % 400000 == 0)
  {
    std::cout << "." << std::flush;
  }
  loadCounter++;
}

int scanCache(std::string value, std::string array[], int arraySize)
{
  for (int i = 0; i < arraySize; ++i)
  {
    if (array[i] == value)
    {
      return i;
    }
  }
  return -1;
}