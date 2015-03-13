#include "parse.h"

// constructor
Parse::Parse()
{
  nTotal = 0;
  nReads = 0;
  nWrites = 0;
}

int Parse::getTotal()
{
  return nTotal;
}

int Parse::getNumOfReads()
{
  return nReads;
}

int Parse::getNumOfWrites()
{
  return nWrites;
}

int Parse::addARead()
{
  nTotal++;
  return ++nReads;
}

int Parse::addAWrite()
{
  nTotal++;
  return ++nWrites;
}