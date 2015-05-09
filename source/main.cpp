
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

  // int cacheSize = 32768;
  // int cacheSize = 16384;
  int cacheLinesL1 = findCacheLines(cacheSizeL1, ADDR_SIZE);
  int cacheLinesL2 = findCacheLines(cacheSizeL2, ADDR_SIZE);
  int bitBlockSizeL1 = findBitBlockSize(cacheLinesL1);
  int bitBlockSizeL2 = findBitBlockSize(cacheLinesL2);
  int tagSizeL1 = findTagSize(ADDR_SIZE, bitBlockSizeL1, OFFSET);
  int tagSizeL2 = findTagSize(ADDR_SIZE, bitBlockSizeL2, OFFSET);

  Cache cacheL1(cacheLinesL1); // instance of cacheL1
  Cache cacheL1(cacheLinesL2); // instance of cacheL1

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

    // std::cout << "Cache Lines: " << cacheLines << std::endl;
      std::cin >> std::hex >> y;
    // std::cout << "Hex Value:" << std::hex << y << std::endl;
    // std::cout << "Decimal Value: " << std::dec << y << std::endl;
    // std::cout << "Binary Value: " << std::bitset<ADDR_SIZE>(y).to_string() << std::endl;

      
    // std::cout << "The LinePos is " << getLinePos(y, cacheLines) << std::endl;
    // std::cout << "Tag Size: " << tagSize << std::endl;
    // std::cout << "Tag Value: " << tagValue << std::endl << std::endl;


    if (x == 1) // Check to see if read 
    {
      traceFile.addARead();
      tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL1);
      if (cacheL1.tagArray[getLinePos(y, cacheLinesL1)] == tagValue)
      {
        numOfHits++;
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << cacheL1.tagArray[getLinePos(y, cacheLines)] << "==" << tagValue << std::endl;
        // std::cout << "HIT!" << std::endl;
      }
      else
      {
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << cacheL1.tagArray[getLinePos(y, cacheLines)] << "!=" << tagValue << std::endl;
        cacheL1.tagArray[getLinePos(y, cacheLinesL1)] = tagValue;
        numOfMisses++;
        // std::cout << "MISS!" << std::endl;
        tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL2);
        if (cacheL1.tagArray[getLinePos(y, cacheLinesL2)] == tagValue)
        {
          numOfHits++;
        }
        else
        {

        }
      }

    }
    else if (x == 0)  // Check to see if write 
    {

      traceFile.addAWrite();
      if (cacheL1.tagArray[getLinePos(y, cacheLinesL1)] == tagValue)
      {
        numOfHits++;
        cacheL1.validArray[getLinePos(y, cacheLinesL1)] = true;
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << cacheL1.tagArray[getLinePos(y, cacheLines)] << "==" << tagValue << std::endl;
        // std::cout << "HIT!" << std::endl;
      }
      else
      {
        // std::cout << getLinePos(y, cacheLines) << " ";
        // std::cout << cacheL1.tagArray[getLinePos(y, cacheLines)] << "!=" << tagValue << std::endl;
        cacheL1.tagArray[getLinePos(y, cacheLinesL1)] = tagValue;
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
}
else if (replacementPolicy=="full")
{

  int hitChecker; // used for FIFO algorithm
  int insertCounterL1 = 0; // used for FIFO algorithm
  int insertCounterL2 = 0; // used for FIFO algorithm

  // code
  while (std::cin >> x)
  {
    // start loading animimation
    loadAnimation(loadCounter);
    // 
    std::cin >> std::hex >> y;

    tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL1);
    int linePosL1 = scanCache(tagValue, cacheL1.tagArray, cacheLinesL1);

    tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL2);
    int linePosL2 = scanCache(tagValue, cacheL1.tagArray, cacheLinesL2);

    if (linePosL1 < 0 && linePosL2 < 0)
    {
      // miss
      numOfMisses++;
      std::cout << "debug: added a miss" << std::endl;

      // FIFO algorithm

        // debugging statements
        // std::cout << "debug: There was a miss. Inserting ";
        // std::cout << traceFile[i] << " into cache line ";
        // std::cout << insertCounter << std::endl;

        // determine where to put the tag

        // if both are not fully scanned
        if (!(cacheL1.isScanned) && !(cacheL1.isScanned))
        {
          // put into cacheL1
          

          if (x == 0) // check if write
          {
            traceFile.addAWrite();
            cacheL1.validArray[insertCounterL1] = true;
          }
          else
          {
            traceFile.addARead();
          }

          cacheL1.tagArray[insertCounterL1++] = tagValue;

          if (insertCounterL1 >= cacheLinesL1)
          {
            cacheL1.isScanned = true;
          }

        }
        else if ((cacheL1.isScanned) && !(cacheL1.isScanned))
        {
          // put into cacheL1
          tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL2);

          if (x == 0) // check if write
          {
            traceFile.addAWrite();
            cacheL1.validArray[insertCounterL2] = true;
          }
          else
          {
            traceFile.addARead();
          }

          cacheL1.tagArray[insertCounterL2++] = tagValue;

          if (insertCounterL2 >= cacheLinesL2)
          {
            cacheL1.isScanned = true;
          }

        }
        else if ((cacheL1.isScanned) && (cacheL1.isScanned))
        {
          // reset isScanned and put into Cache L1

          insertCounterL1 = 0;
          insertCounterL2 = 0;

          cacheL1.isScanned = false;
          cacheL1.isScanned = false;

          // put into cacheL1
          tagValue = std::bitset<ADDR_SIZE>(y).to_string().substr(0, tagSizeL1);

          if (x == 0) // check if write
          {
            traceFile.addAWrite();
            cacheL1.validArray[insertCounterL1] = true;
          }
          else
          {
            traceFile.addARead();
          }
          cacheL1.tagArray[insertCounterL1++] = tagValue;
        }
        else
        {
          std::cout << "Error: Something went wrong :C" << std::endl;
          return -1;
        }
    }
    else
    {
      // hit
      if (x == 0) // add a write
      {
        traceFile.addAWrite();
      }
      else
      {
        traceFile.addARead();
      }
      numOfHits++;
    }
  }


}
else
{
  return 1;
}




 

  

  // // need to change cacheLines into cacheLinesL1
  // std::string *cacheL1.tagArrayL1 = new std::string[cacheLinesL1];
  // initStringArray(cacheL1.tagArrayL1, cacheLinesL1, "null");

  // // need to change cacheLines into cacheLinesL2
  // std::string *cacheL1.tagArrayL2 = new std::string[cacheLinesL1];
  // initStringArray(cacheL1.tagArrayL2, cacheLinesL1, "null");

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << cacheL1.tagArray[i] << std::endl;
  // }

  // // need to change cacheLines into cacheLinesL1
  // bool *cacheL1.validArrayL1 = new bool[cacheLines];
  // initBoolArray(cacheL1.validArrayL1,  cacheLines, false);

  // // need to change cacheLines into cacheLinesL2
  // bool *cacheL1.validArrayL2 = new bool[cacheLines];
  // initBoolArray(cacheL1.validArrayL2,  cacheLines, false);

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << cacheL1.validArray[i] << std::endl;
  // }
  // 

  // direct mapping starts here

  std::cout << "\b\b\b\b\b\b\b\b\b\bLoading Done!" << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << "Memory refreneces read from file:" << std::endl;
  std::cout << traceFile.getTotal() << " Total" << std::endl;
  std::cout << traceFile.getNumOfReads() << " Reads" << std::endl;
  std::cout << traceFile.getNumOfWrites() << " Writes" << std::endl;

  // for (int i = 0; i < cacheLines; ++i)
  // {
  //   std::cout << cacheL1.tagArray[i] << " " << cacheL1.validArray[i] << std::endl;
  // }

  // std::cout << "  Hits: " << numOfHits << std::endl;
  // std::cout << "Misses: " << numOfMisses << std::endl << std::endl;
  std::cout << "-------------------------------------------------------------" << std::endl;
  std::cout << "  Hits: " << getPercentage(numOfHits, numOfHits+numOfMisses) << " \%" <<std::endl;
  std::cout << "Misses: " << getPercentage(numOfMisses, numOfHits+numOfMisses) <<  " \%" << std::endl << std::endl;

  return 0;
}
