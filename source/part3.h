#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "part2.h"

/**
 * This is a class for cache
 */
class Cache
{
  public:
    // VARIABLES
    std::string *tagArray; // tag array
    bool *validArray; // valid array
    bool isScanned;
    int hit; // keeps track of the number of hits in the cache
    int miss; // keeps track of the number of misses in the cache
    // CONSTRUCTORS
    Cache(int cacheLines);
    // METHODS
    /**
     * This increments the hit counter of the cache
     */
    void addHit();
    /**
     * This increments this miss counter of the cache
     */
    void addMiss();
    /**
     * This gets the value of the hit counter for the cache
     * @return Integer value of the hit counter
     */
    int getHits();
    /**
     * This gets the value of the miss counter for the cache
     * @return Integer value of the miss counter
     */
    int getMisses();
    /**
     * This inserts the tag into a specified position into
     * the cache's tagArray
     * @param tag    The tag to be inserted
     * @param tagPos The position of insertion 
     */
    void insertTag(std::string tag, int tagPos);
    /**
     * This will get the tag from a specified postion of the
     * cache's tagArray
     * @param  pos position where the tag will be found
     * @return     The tag itself (string)
     */
    std::string getTag(int pos);

    /**
     * This update the valid bit of this cache's validArray
     * @param   pos     Position where the valide bit
     *                  will be found
     */
    void updateValid(int pos);
};

/**
 * This scans an array for a specific string.
 * @param  value     The string to search for in the array
 * @param  array     The array to search
 * @param  arraySize The size of the array 
 * @return           True if found
 *                   False if not found
 */
bool scanCache(std::string value, std::string array[], int arraySize);


void loadAnimation(int &loadCounter);
