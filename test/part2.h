
#include <iostream>
#include <string>
#include <vector>

//////////////////////
// MemoryWord Class //
//////////////////////

class MemoryWord 
{
friend class MemoryBlock;
private:
	std::string address;
	int wordId;
public:
	MemoryWord(std::string, int);
	std::string getAddress();
	int getWordId();
};

///////////////////////
// MemoryBlock Class //
///////////////////////

class MemoryBlock
{
private:
	int blockId;
public:
	std::vector<MemoryWord*> words;
	MemoryBlock(int);
	int getBlockId();
	int getBlockSize();
	void addWord(std::string, int);
};
