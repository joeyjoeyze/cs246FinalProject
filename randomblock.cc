#include "randomblock.h"

RandomBlock::RandomBlock(const int& level=0)
:inFile(NULL),sum(0),probBlock(0){
	setLevel(level);
}

RandomBlock::RandomBlock(const string& levelZero, const int& level=0)
:inFile(NULL),sum(0),probBlock(0){
	inFileName[0] = levelZero;
	setLevel(level);
}

RandomBlock::~RandomBlock(){
	if(level == 0) inFile.close();
}

void RandomBlock::setLevel(const int& level){
	this->level = level;
	if(level == 0){
		inFile.open(inFileName[0].c_str());
	}else{
		inFile.open(inFileName[level].c_str());
		string temp;
		delete probBlock;
		probBlock = new int[totalBlock];
		stringstream ss;
		int total = 0;
		for(int i=0;i<totalBlock;i++){
			ss.clear();
			inFile >> temp;
			ss << temp;
			ss >> totalBlock[i];
			total = total + totalBlock[i];
		}
		sum = total;
		inFile.close();
	}
}

void RandomBlock::levelUp(){
	if(level >= (totalLevel - 1)) return;
	if(level == 0){
		inFile.close();
	}
	level++;
	setLevel(level);
}

void RandomBlock::levelDown(){
	if(level <= 0) return;
	level--;
	setLevel(level);
}

Block * RandomBlock::getBlock(){
	if(level == 0){
		if(inFile.eof()){
			inFile.close();
			inFile.open(inFilename[0]);
		}
		char temp;
		inFile >> temp;
		for(int i=0;i<totalBlock;i++){
			if(temp == blockType[i]){
				Block * ret = new Block(temp);
				return ret;
			}
		}
	}else{
		int random = (rand() % (sum - 1)) + 1;
		for(int i=0;i<totalBlock;i++){
			random = random - probBlock[i];
			if(random <= 0){
				Block * ret = new Block(blockType[i]);
				return ret;
			}
		}
	}
}
