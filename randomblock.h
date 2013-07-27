#ifndef __RANDBLOCK_H_
#define __RANDBLOCK_H_
#include "PRNG.h"
#include "block.h"
#include<iostream>
#include<fstream>

static const int totalBlock = 7;
static const int totalLevel = 4;
class RandomBlock(){
	std::ifstream inFile;
	int sum;
	int level;
	int probBlock[totalBlock];
	char blockType[totalBlock] = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};
	String inFileName[totalBlock] = {"sequence.txt", "level1.txt", "level2.txt", "level3.txt"};
	public:
	RandomBlock(const int&);
	RandomBlock(const string&, const int&);
	void setLevel(const int&);
	void levelUp();
	void levelDown();
	Block * getBlock();
}