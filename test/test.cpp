#include <iostream>
#include <cstdlib>
#include <math>

static const int ADDR_SIZE = 32; // Address size will always be 32 bits
static const int OFFSET = 5; // Offset size will always be 5 bits

/**
* USAGE: int cache_lines = findCacheLines(argv[2], ADDR_SIZE);
*/
int findCacheLines(int cache_size, int addr_size)
{
 	return cache_size / addr_size; 
}

/**
* USAGE: int bit_addr = findBitAddress(cache_lines);
* USAGE: int bit_addr = findBitAddress(findCacheLines(argv[2], ADDR_SIZE));
*/
int findBitAddress(int cache_lines)
{
 	return  log2(cache_lines);
}

/**
* USAGE: int tag_size = findTagSize(ADDR_SIZE, bit_bAddr, OFFSET);
*/
int findTagSize(int addr_size, int bit_addr, int offset)
{
 	return addr_size - bit_addr - offset; 
}

void initValidArray(bool array[]) // Initializing the value of the Valid Array
{
  for (int i = 0; i < 10; i++)
  {
	 array[i] = false;
  }
}

void initTagArray(int array[], int tagSize) // Initializing the values of the Tag Array, must past in the size as a parameter
{
	for (for i = 0; i < tagSize; i++)
}

int main()
{
  	int tagArray[10]; // The array for the tag binary or hexidecimal
    bool validArray[10]; // The array for the valid bits
  
  	int tagSize = 0; //

  	initValidArray(validArray);
  
    for (int i = 0; i < 10; i++)
    {
       std::cout << validArray[i] << std::endl; // Check the values of what's currently in the array
    }
 
  return 0;
}

http://stackoverflow.com/questions/2611764/can-i-use-a-binary-literal-in-c-or-c