#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

/**
 * If the return value is more than -1, then the scan produces
 * a hit and returns the position in cache where the hit was found.
 * Otherwise, the return value is -1 and there was a miss.
 * @param  value     Value to check
 * @param  array     Pass in cache
 * @param  arraySize cache lines 
 * @return           -1 if miss
 *                   hit if > -1
 */
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