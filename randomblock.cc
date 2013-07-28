#include "randomblock.h"
using namespace std;

RandomBlock::RandomBlock(const int& level)
:sum(0),level(level),totalBlock(0),totalLevel(0){
	initBlock();
	initFile();
	setLevel(level);
}

RandomBlock::RandomBlock(const string& levelZero, const int& level)
:sum(0),level(level),totalBlock(0),totalLevel(0){
	initBlock();
	initFile();
	inFileName[0] = levelZero;
	setLevel(level);
}

RandomBlock::~RandomBlock(){
	delete blockType;
	delete inFileName;
	delete probBlock;
	if(level == 0) inFile.close();
}

void RandomBlock::initBlock(){
	ifstream in;
	char temp  = '\0';
	int num;
	
	in.open(blockInfo.c_str());
	in >> num;
	totalBlock = num;

	blockType = new char [totalBlock];
	int pos = 0;
	char prev = temp;
	while(in >> temp){
		if(temp >= 'A' && temp <= 'Z' && temp != prev){
			probBlock[pos] = temp;
			pos++;
		}
		prev = temp;
	}
}

void RandomBlock::initFile(){
	ifstream in;
	string temp;
	int num;
	
	in.open(fileInfo.c_str());
	in >> num;
	totalLevel = num;
	
	inFileName = new string [num];
	int pos = 0;
	while(in >> temp){
		inFileName[pos] = temp;
		pos++;
	}
}

void RandomBlock::setLevel(const int& level){
	this->level = level;
	if(level == 0){
		inFile.open(inFileName[0].c_str());
	}else{
		inFile.open(inFileName[level].c_str());
		string temp;
		stringstream ss;
		int total = 0;
		for(int i=0;i<totalBlock;i++){
			ss.clear();
			inFile >> temp;
			ss << temp;
			ss >> probBlock[i];
			total = total + probBlock[i];
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
			inFile.open(inFileName[0].c_str());
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
