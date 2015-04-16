#include "part2.h"

// class MemoryWord 
// {
// private:
// 	std::string address;
// 	int wordId;
// public:
// 	std::string getAddress();
// 	int getWordId();
// };

MemoryWord::MemoryWord(std::string addr, int wordPos)
{
	address = addr;
	wordId = wordPos;
}

MemoryBlock::MemoryBlock(int blockPos)
{
	blockId = blockPos;
}

/////////////////////////
// MemoryWord Funtions //
/////////////////////////

std::string MemoryWord::getAddress()
{
	return address;
}

int MemoryWord::getWordId()
{
	return wordId;
}

///////////////////////////
// MemoryBlock Functions //
///////////////////////////

// class MemoryBlock
// {
// private:
// 	std::vector<MemoryWord*> words;
// 	int blockId;
// public:
// 	int getBlockId();
// 	void addWord(std::string, int);
// }

int MemoryBlock::getBlockId()
{
	return blockId;
}

void MemoryBlock::addWord(std::string addr, int wordPos)
{
	words.push_back(new MemoryWord(addr, wordPos));
}

int MemoryBlock::getBlockSize()
{
	return words.size();
}
