
#include "parse.h"
// #include "part2.h"
#include "part3.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>


int main(int argc, char const *argv[])
{

  Parse traceFile; // this will handle the tracefile

  // determines replacement policy in program flow // defaults to direct
  std::string replacementPolicy = "direct";

  // storage for the trace file into "main memory"

  int x; // for read/write
  int y; // for the hex value

  // traceFile.getArguments(argc, argv);

  int cacheSizeL1 = 0; // size of the cache 
  int cacheSizeL2 = 0; // size of the cache 

  int loadCounter = 0;

  std::string tagValue;

  int numOfHits = 0;
  int numOfMisses = 0;

  traceFile.getArguments(argc, argv, cacheSizeL1, cacheSizeL2, replacementPolicy);

  std::cout << "-------------------------------------------------------------" << std::endl; 

  // int cacheSize = 32768;
  // int cacheSize = 16384;
  int cacheLinesL1 = findCacheLines(cacheSizeL1, ADDR_SIZE);
  int cacheLinesL2 = findCacheLines(cacheSizeL2, ADDR_SIZE);
  int bitBlockSizeL1 = findBitBlockSize(cacheLinesL1);
  int bitBlockSizeL2 = findBitBlockSize(cacheLinesL2);
  int tagSizeL1 = findTagSize(ADDR_SIZE, bitBlockSizeL1, OFFSET);
  int tagSizeL2 = findTagSize(ADDR_SIZE, bitBlockSizeL2, OFFSET);

  Cache CacheL1(cacheLinesL1); // instance of CacheL1
  Cache CacheL2(cacheLinesL2); // instance of CacheL1

  ////////////////////////////
  // PARSING / PROGRAM FLOW //
  ////////////////////////////

  std::cout << "Loading" << std::flush;

  // mayur
  if(replacementPolicy=="direct")
  {
    while (std::cin >> x) // credit to epstein
    {
    // loading animation
    loadAnimation(loadCounter);
    std::cin >> std::hex >> y; // get the address from the trace file
    
      // determine if it is a read or write
      if (x == 0) // if a write
      {
        traceFile.addAWrite();
      }
      else if (x == 1)
      {
        // add a read
        traceFile.addARead();
      }
      else
      {
        // error when reading the file
        std::cout << "Error: Could not determine if read/write. Exiting Program";
        std::cout << std::endl;
        // exit program with error code
        return 1;
      }

      // handling the tag value
      tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL1);
      if (CacheL1.getTag(getLinePos(y, cacheLinesL1)) == tagValue)
      {
        // mark as a hit
        CacheL1.addHit();
      }
      else
      {
        // mark as a miss
        CacheL1.addMiss();
        // insert tag into level 1 tag array
        CacheL1.insertTag(tagValue, getLinePos(y, cacheLinesL1));
        // if a write, then update validArray for the cache
        if (x == 0)
        {
          CacheL1.updateValid(getLinePos(y, cacheLinesL1)); // create a function for this
        }

        tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL2);
        if(CacheL2.getTag(getLinePos(y, cacheLinesL2)) == tagValue)
        {
          // mark as a cache level 2 hit
          CacheL2.addHit();
        }
        else
        {       
          // mark as a cache level 2 miss
          CacheL2.addMiss();
          // insert tag into level 2 tagArray
          CacheL2.insertTag(tagValue, getLinePos(y, cacheLinesL2));
          // if a write, then update validArray for the cache
          if(x == 0)
          {
            CacheL1.updateValid(getLinePos(y, cacheLinesL1));
          }
        }
      }
  }
}
else if (replacementPolicy=="full")
{

  int hitChecker; // used for FIFO algorithm
  int insertCounterL1 = 0; // used for FIFO algorithm
  int insertCounterL2 = 0; // used for FIFO algorithm

  while (std::cin >> x)
  {
    // start loading animation
    loadAnimation(loadCounter);
    // get the addr from the trace
    std::cin >> std::hex >> y;

    // check for read and writes
    if (x == 0) // if a write
    {
      traceFile.addAWrite();
    }
    else if (x == 1) // if a read
    {
      traceFile.addARead();
    }

    // check for L1 hit
    tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL1);
    bool isFound = scanCache(tagValue, CacheL1.tagArray, cacheLinesL1);
    // if hit, then
    if (isFound)
    {
      // increment hit counter
      CacheL1.addHit();
    }
    else
    {
      // check if write
      if (x == 0)
      {
        // set valid bit to true  
        CacheL1.updateValid(insertCounterL1);
      }
      // increment miss counter
      CacheL1.addMiss();
      // insert tag into cache
      CacheL1.insertTag(tagValue, insertCounterL1++);
      // check for insertCounter reset
      if (insertCounterL1 >= cacheLinesL1)
      {
        insertCounterL1 = 0;
      }
      // check for L2 hit
      tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL2);
      isFound = scanCache(tagValue, CacheL2.tagArray, cacheLinesL2);
      // if hit, then
      if (isFound)
      {
        // increment hit counter
        CacheL2.addHit();
      }
      else
      {
        // check if write
        if (x == 0)
        {
          // set valid bit to true  
          CacheL2.updateValid(insertCounterL2);
        }
        // increment miss counter
        CacheL2.addMiss();
        // insert tag into cache
        CacheL2.insertTag(tagValue, insertCounterL2++);
        // check for insertCounter reset
        if (insertCounterL2 >= cacheLinesL2)
        {
          insertCounterL2 = 0;
        }
      }   
    }
  }
  // std::cout << "insertCounterL1 = " << insertCounterL1 << std::endl;
  // std::cout << "insertCounterL2 = " << insertCounterL2 << std::endl;

}
else
{
  std::cout << "Error: Something went wrong... exiting program." << std::endl;
  return 1;
}

  std::cout << "\b\b\b\b\b\b\b\b\b\bLoading Done!" << std::endl;

  std::cout << "-------------------------------------------------------------" << std::endl;

  std::cout << "Memory refreneces read from file:" << std::endl;
  std::cout << "  " << traceFile.getTotal() << " Total" << std::endl;
  std::cout << "  " << traceFile.getNumOfReads() << " Reads" << std::endl;
  std::cout << "  " << traceFile.getNumOfWrites() << " Writes" << std::endl;

  std::cout << "-------------------------------------------------------------" << std::endl;

  std::cout << "Simulation Execution:" << std::endl;
  std::cout << "  L1   Hits: " << getPercentage(CacheL1.getHits(), CacheL1.getHits()+CacheL1.getMisses()) << " \%" <<std::endl;
  std::cout << "  L1 Misses: " << getPercentage(CacheL1.getMisses(), CacheL1.getHits()+CacheL1.getMisses()) <<  " \%" << std::endl << std::endl;
  std::cout << "  L2   Hits: " << getPercentage(CacheL2.getHits(), CacheL2.getHits()+CacheL2.getMisses()) << " \%" <<std::endl;
  std::cout << "  L2 Misses: " << getPercentage(CacheL2.getMisses(), CacheL2.getHits()+CacheL2.getMisses()) <<  " \%" << std::endl;

  std::cout << "=============================================================" << std::endl;

  return 0;
}
