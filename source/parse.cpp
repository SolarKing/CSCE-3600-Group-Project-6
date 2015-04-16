/**
* TODO
* [ ] implement -sizeL1 xx
* [ ] implement -sizeL2 xx
* [ ] implement -type direct/full
* [ ] implement -write-policy through/back
*/

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


