#ifndef __RANDBLOCK_H_
#define __RANDBLOCK_H_
#include "block.h"
#include "board.h"
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

static const std::string blockInfo = "blocks.txt";
static const std::string fileInfo = "levels.txt";
class RandomBlock{
	Board* board;
	std::ifstream inFile;
	int sum;
	int level;
	int totalBlock;
	int totalLevel;
	Block ** origBlocks;	//original blocks
	std::string * inFileName;
	int * probBlock;
	void initBlock();
	void initFile();
	public:
	RandomBlock(Board* board, const int& level=0);
	RandomBlock(Board* board, const std::string& levelZero, const int& level=0);
	~RandomBlock();
	void setLevel(const int&);
	void levelUp();
	void levelDown();
	Block * getBlock();
};

#endif
