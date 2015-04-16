// #ifndef PARSE_H
// #define PARSE_H

#include <iostream>
#include <string>
#include <vector>

class Parse
{
private:
  // stores the total number of reads
  // and writes in the parse file
  int nTotal;
  // stores the total number of reads
  int nReads;
  // stores the total number of writes
  int nWrites;

public:

  // constructor
  Parse();

  /**
   * This returns the total number of reads and writes
   * in the trace file. 
   * @return This returns nTotal
   */
  int getTotal();

  /**
   * This returns the number of reads in the trace file
   * @return This returns nReads
   */
  int getNumOfReads();

  /**
   * This returns the number of writes in the trace file
   * @return This returns nWrites
   */
  int getNumOfWrites();

  /**
   * This will increment the value of nReads by 1 and the nTotal
   * by 1 (i.e. nRead++, nTotal++)
   * @return This returns new value of nReads
   */
  int addARead();

  /**
   * This will increment the value of nWrites by 1 and the nTotal
   * by 1 (i.e. nWrites++, nTotal++)
   * @return This returns new value of nWrites
   */
  int addAWrite();
};

// #endif