#include "test.h"

class Cache {
  private:
    std::string *tagArray; // pointer for tag storage
    int hit; // keeps track of hits for this cache
    int miss; // keeps track of misses for this cache
  public:
    // constructor
    Cache(int arrayLength);
    // initializes the tag array
    void initTagArray(int arrayLength);
    // increment hit
    void addHit();
    // increment miss
    void addMiss();
    // insert a tag into the tag array
    void insertTag(std::string tag, int tagPos);
    // get the tag value from the tag array
    std::string getTag(int pos);
    // get the number of hits
    int getHits();
    // get the number of misses
    int getMisses();
};

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

void Cache::initTagArray(int arrayLength) {
  for(int i = 0; i < arrayLength; i++)
  {
    tagArray[i] = "null";
  }
}

Cache::Cache(int arrayLength)
{
  tagArray = new std::string [arrayLength];
  hit = 0;
  miss = 0;
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

int main(int argc, char const *argv[])
{

  // create small cache L1
  Cache CacheL1(3);
  // create larger cache L2
  Cache CacheL2(6);
  // create traceFile
  std::string traceFile[12];

  for(int i = 0; i < 12; i++)
  {
    traceFile[i] = std::to_string(i%6);
    std::cout << "TraceFile[" << std::to_string(i) << "] = ";
    std::cout << traceFile[i] << std::endl;
  }

  for(int i = 0; i < 12; i++)
  {
    // implement direct mapping behavoir
    // check for L1 hit

    // std::cout << "-------------------------------------" << std::endl;

    // std::cout << "debug: CacheL2.getTag(" << i%6 << ") == ";
    // std::cout << CacheL2.getTag(i%6) << std::endl;

    // std::cout << "debug: traceFile[" << i << "] == ";
    // std::cout << traceFile[i] << std::endl;

    if (CacheL1.getTag(i%3) == traceFile[i])
    {
      // mark as a hit
      CacheL1.addHit();
      std::cout << "Added a hit to L1..." << std::endl;
    }
    else
    {
      // mark as a miss
      CacheL1.addMiss();
      // insert tag into level 1 tag array
      CacheL1.insertTag(traceFile[i], i%3);

      if (CacheL2.getTag(i%6) == traceFile[i])
      {
        // mark as a cache level 2 hit
        CacheL2.addHit();
        std::cout << "Added a hit to L1..." << std::endl;
      }
      else
      {
        // mark as a cache level 2 miss
        CacheL2.addMiss();
        // insert tag into level 2 tag array
        CacheL2.insertTag(traceFile[i], i%6);
      }
    }
  } 

  std::cout << "Number of L1 hits: " << CacheL1.getHits() << std::endl;
  std::cout << "Number of L1 misses: " << CacheL1.getMisses() << std::endl;

  std::cout << "Number of L2 hits: " << CacheL2.getHits() << std::endl;
  std::cout << "Number of L2 misses: " << CacheL2.getMisses() << std::endl;

  std::cout << "This is working" << std::endl;

  return 0;
}
