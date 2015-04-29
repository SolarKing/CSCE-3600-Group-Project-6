#include "test.h"

int main(int argc, char const *argv[])
{

  int miss = 0;
  int hit = 0;

  int insertCounter = 0;
  int scanCounter = 0;

  std::string testCache[10];
  std::string traceFile[20] = {
    "1",
    "2",
    "1",
    "9",
    "3",
    "1",
    "4",
    "7",
    "6",
    "8",
    "5",
    "3",
    "13",
    "14",
    "15",
    "1",
    "2",
    "1",
    "15",
    "1",
  };

  for (int i = 0; i < 20; ++i)
  {
    std::cout << traceFile[i] << std::endl;
  }

  for (int i = 0; i < 10; ++i)
  {
    testCache[i] = "null";
    std::cout << testCache[i] << std::endl;
  }

  // FIFO algorithm
  int hitChecker;
  for (int i = 0; i < 20; ++i)
  {
    hitChecker = scanCache(traceFile[i], testCache, 10);
    if (hitChecker < 0) 
    {
      if (insertCounter >= 10)
      {
        insertCounter = 0;
      }
      std::cout << "There was a miss. Inserting ";
      std::cout << traceFile[i] << " into cache line ";
      std::cout << insertCounter << std::endl;

      testCache[insertCounter++] = traceFile[i];
      miss++;
    }
    else if (hitChecker > -1)
    {
      std::cout << "There was a hit! Found value ";
      std::cout << testCache[hitChecker] << " in cache line ";
      std::cout << hitChecker << std::endl;
      hit++;
    }
  }


  std::cout << "This is working" << std::endl;
  return 0;
}