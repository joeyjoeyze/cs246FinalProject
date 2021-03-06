#include "randomblock.h"
using namespace std;

RandomBlock::RandomBlock(Board* board, const int& level, const int& seed)
:board(board), sum(0),level(level),totalBlock(0),totalLevel(0){
	srand(seed);
	initBlock();
	initFile();
	setLevel(level);
}

RandomBlock::RandomBlock(Board* board, const string& levelZero, const int& level, const int& seed)
:board(board), sum(0),level(level),totalBlock(0),totalLevel(0){
	srand(seed);
	initBlock();
	initFile();
	inFileName[0] = levelZero;
	setLevel(level);
}

RandomBlock::~RandomBlock(){
	for(int i=0;i<totalBlock;i++){
		delete origBlocks[i];
	}
	delete [] origBlocks;
	delete [] inFileName;
	delete [] probBlock;
	if(level == 0) inFile.close();
}

void RandomBlock::initBlock(){
	ifstream in;
	in.open(blockInfo.c_str());

	in >> totalBlock;
	origBlocks = new Block*[totalBlock];
	probBlock = new int [totalBlock];
	Cell* parts[4];

	for (int i=0; i<totalBlock; ++i){
		int row = 3;
		int col = 0;
		int numCells = 0;
		int colour;
		in >> colour;
		in.get();
		stringstream ss;
		char c;
		while (numCells < 4){
			c = in.get();
			ss << c;
			if (c=='\n'){
				row++;
				col = -1;
			} else if (c!=' '){
				parts[numCells] = board->getCell(row, col);
				numCells++;
			}
			col++;
		}
		origBlocks[i] = new Block(c, colour, ss.str(), parts);
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
	if(level == 0) inFile.close();				//close the file opened by level zero
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

int RandomBlock::levelUp(){
	if(level >= (totalLevel - 1)){}
	else{
        if(level == 0) inFile.close();
        level++;
        setLevel(level);
	}
	return level;
}

int RandomBlock::levelDown(){
	if(level <= 0) {}
	else {
        level--;
        setLevel(level);
	}
	return level;
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
			if(temp == origBlocks[i]->getType()){
				bool available = true;
				for(int j=0;j<4;j++){
					available = available && (((origBlocks[i])->getPart(j))->getType() == ' ');
				}
				if(available){
					Block * ret = new Block(*origBlocks[i]);
					ret->setLevel(level);
					return ret;
				}else {
					return NULL;
				}
			}
		}
	}else{
		int random = (rand() % (sum - 1)) + 1;
		for(int i=0;i<totalBlock;i++){
			random = random - probBlock[i];
			if(random <= 0){
				bool available = true;
				for(int j=0;j<4;j++){
					available = available && (((origBlocks[i])->getPart(j))->getType() == ' ');
				}
				if(available){
					Block * ret = new Block(*origBlocks[i]);
					ret->setLevel(level);
					return ret;
				}else{
					return NULL;
				}
			}
		}
	}
	return 0;
}
