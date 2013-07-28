#include "game.h"

#include "block.h"
#include "board.h"
#include "randomblock.h"
using namespace std;

Game::Game(const int& level, bool GUI)
:score(0),level(level),highScore(0),initialLevel(level),GUI(GUI){
	board = new Board;
	randBlock = new RandomBlock(level);
}

Game::Game(const String& fileName, const int& level, bool GUI)
:score(0),level(level),highScore(0),initialLevel(level),GUI(GUI){
	board = new Board;
	randBlock = new RandomBlock(fileName,level);
}

Game::~Game(){
	for(vector<Block *>::iterator vi=blocks.begin();vi!=blocks.end();++vi){
	//using iterators to delete all the block pointers in Blocks
		delete *vi
	}
	blocks.clear();
	delete randBlock;
	delete board;
	
}

void updateScore(const int& newScore){	//called when a row is cancelled, could implement without parameter
	if(newScore > highScore) highScore = newScore;
	score = newScore;
}

bool Game:command(const string& cmd){	//finds and calls the command from main in block, return value determines to spawn a new block or not
	Block * currentBlock = blocks[(blocks.size() - 2)];
	if(cmd == "left"){
		currentBlock->shift(board, 1);
	}else if(cmd == "right"){
		currentBlock->shift(board, 2);
	}else if(cmd == "down"){
		currentBlock->shift(board, 0);
	}else if(cmd == "clockwise"){
		currentBlock->rotate(board, 1);
	}else if(cmd == "counterclockwise"){
		currentBlock->rotate(board, 0);
	}else if(cmd == "drop"){
		for(int i=0;i<15;i++){
			currentBlock->shift(board, 0);
		}
		blocks.push_back(newBlock());
	}else if(cmd == "levelup"){
		randBlock->levelUp();
	}else if(cmd == "leveldown"){
		randBlock->levelDown();
	}else if(cmd == "restart"){
		delete board;
		board = new Board;
		score = 0;
		level = initLevel;
		highScore = 0;
		randBlock->setLevel(level);
		for(vector<Block *>::iterator vi=blocks.begin();vi!=blocks.end();++vi){
		//using iterators to delete all the block pointers in Blocks
			delete *vi
		}
		blocks.clear();
		blocks.push_back(newBlock());
		blocks.push_back(newBlock());
	}else{
		cerr << "BAD COMMAND" << endl;
	}
}

void newBlock(){
	Block * temp = randBlock->getBlock();
	temp.setParts();
}

ostream& operator<<(ostream& out, const Game& g){
	out << "Level:" << setw(spacing + 3) << g.level << endl;
	out << "Score:" << setw(sapcing + 3) << g.score << endl;
	out << "Hi Score:" << setw(spacing) << g.highScore << endl;
	out << "----------" << endl;
	out << g.board << endl;
	out << "----------" << endl;
	out << "Next:" << endl;
	out << g.blocks[(blocks.size() - 1)] << endl;
	return out;
}
