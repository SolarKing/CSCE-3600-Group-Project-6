#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <string>

/**
 * This class stores the number of reads and writes, within
 * a trace file, and has methods to to manipulate and
 * obtain those values.
 */
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

  /**
   * This gets the arguments passed into the command line and stores
   * the value within an instance of the Parse class. 
   * @param  argc Number of arguments to be read
   * @param  argv The arguments to be read
   * @return      Returns 1 for faliure, otherwise return 0
   */
  int getArguments(int argc, char const *argv[]);
};

#endif