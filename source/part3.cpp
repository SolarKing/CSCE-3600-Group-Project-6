#include "part3.h"



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

bool scanCache(std::string value, std::string array[], int arraySize)
{
  for (int i = 0; i < arraySize; ++i)
  {
    // std::cout << "-----------------------------" << std::endl;
    // std::cout << "debug: array[i] == " << array[i] << std::endl;
    // std::cout << "debug: value == " << value << std::endl;
    if (array[i] == value)
    {
      return true;
    }
  }
  return false;
}

// CACHE METHODS

Cache::Cache(int cacheLines)
{
  hit = 0;
  miss = 0;
  isScanned = false;

  tagArray = new std::string[cacheLines];
  initStringArray(tagArray, cacheLines, "null");

  validArray = new bool[cacheLines];
  initBoolArray(validArray,  cacheLines, false);
}

int Cache::getHits()
{
  return hit;
}

int Cache::getMisses()
{
  return miss;
}

std::string Cache::getTag(int pos)
{
  return tagArray[pos];
}

void Cache::insertTag(std::string tag, int tagPos)
{
  tagArray[tagPos] = tag;
}

// determine where the tag should be
int findTagPos(int traceFilePos, int cacheLines)
{
  return traceFilePos % cacheLines;
}

// increment Cache hit
void Cache::addHit()
{
  hit++;
}
// increment Cache miss
void Cache::addMiss()
{
  miss++;
}

void Cache::updateValid(int pos)
{
  validArray[pos] = true;
}


