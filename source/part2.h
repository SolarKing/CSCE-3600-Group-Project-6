#include <iostream>
#include <cstdlib>
#include <cmath> // log2()
#include <iomanip>
#include <sstream>

static const int ADDR_SIZE = 32; // Address size will always be 32 bits (for this assignment)
static const int OFFSET = 5; // Offset size will always be 5 bits (for this assignment)

/**
 * This finds the number of cache lines in a 2^n sized cache
 * @param  cache_size Size of the cache in bits
 * @param  addr_size  Size of the an address in bits (usually 32)
 * @return            Returns the number of lines in the cache
 */
int findCacheLines(int cache_size, int addr_size);

/**
 * This finds the size block bit address in bits (i.e. 10 bits for a 32K cache)
 * @param  cache_lines The number of lines in the cache (see findCacheLines())
 * @return             Returns the size of the block bit address in bits.
 */
int findBitBlockSize(int cache_lines);

/**
 * This finds the size of the tag line (depends on the size of the cache)
 * @param  addr_size Size of the address (usually 32 bits)
 * @param  b_size    Size of the block bit address
 * @param  offset    Size of the offset (usually 5)
 * @return           Returns the size of the tag line in bits (i.e 17 bits for a 32K cache)
 */
int findTagSize(int addr_size, int b_size, int offset);

/**
 * Initialize the values of a type bool array to either true or false
 * @param array      Array of type bool
 * @param array_size Size of the array
 * @param boolean    Either "true" or "false"
 */
void initBoolArray(bool array[], int array_size, bool boolean);

/**
 * Initialize the values of a type int array to a specified integer
 * @param array      Array of type int
 * @param array_size Size of the array
 * @param value      Value used to initalize each entry in the array
 */
void initIntArray(int array[], int array_size, int value);

/**
 * Find the cache line position for a specific address passed in as a hexadecimal number
 * @param  base12      A hexadecimal address
 * @param  cache_lines The number of lines in the cache (see findCacheLines())
 * @return             Returns the line position
 */
int getLinePos(int base12, int cache_lines);
