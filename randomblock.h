#ifndef __RANDBLOCK_H_
#define __RANDBLOCK_H_
#include "block.h"
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

static const std::string blockInfo = "blocks.txt";
static const std::string fileInfo = "levels.txt";
class RandomBlock{
	std::ifstream inFile;
	int sum;
	int level;
	int totalBlock;
	int totalLevel;
	char * blockType;
	std::string * inFileName;
	int * probBlock;
	void initBlock();
	void initFile();
	public:
	RandomBlock(const int& level=0);
	RandomBlock(const std::string& levelZero, const int& level=0);
	~RandomBlock();
	void setLevel(const int&);
	void levelUp();
	void levelDown();
	Block * getBlock();	
}