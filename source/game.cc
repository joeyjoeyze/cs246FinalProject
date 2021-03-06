#include "game.h"
#include "block.h"
#include "board.h"
#include "randomblock.h"
#include<cmath>
using namespace std;

Game::Game(const int& level, const int& seed, bool GUI)
:gameOver(false),score(0),level(level),highScore(0),initLevel(level),GUI(GUI){
	blocks = new vector<Block *>;
	board = new Board(15,10,3,0,GUI);
	randBlock = new RandomBlock(board, level, seed);
	blocks->push_back(randBlock->getBlock());
	blocks->push_back(randBlock->getBlock());
	board->XwindowUpdate(blocks->at(1)->getOutput(), blocks->at(1)->getColour());
	board->XwindowUpdate(level, score, highScore);
	(blocks->at(0))->activate(board);
}

Game::Game(const string& fileName, const int& level, const int& seed, bool GUI)
:gameOver(false),score(0),level(level),highScore(0),initLevel(level),GUI(GUI){
	blocks = new vector<Block *>;
	board = new Board(15,10,3,0,GUI);
	randBlock = new RandomBlock(board, fileName, level, seed);
	blocks->push_back(randBlock->getBlock());
	blocks->push_back(randBlock->getBlock());
	board->XwindowUpdate(blocks->at(1)->getOutput(), blocks->at(1)->getColour());
	board->XwindowUpdate(level, score, highScore);
	(blocks->at(0))->activate(board);
}

Game::~Game(){
	for(vector<Block *>::iterator vi=blocks->begin();vi!=blocks->end();++vi){
	//using iterators to delete all the block pointers in Blocks
		delete *vi;
	}
	blocks->clear();
	delete blocks;
	delete randBlock;
	delete board;

}

void Game::updateScore(const int& newScore){	//called when a row is cancelled, could implement without parameter
	//if(newScore > highScore) highScore = newScore;
	score = score + newScore;
	if(score > highScore) highScore = score;
	board->XwindowUpdate(level, score, highScore);
}

void Game::command(const string& cmd){	//finds and calls the command from main in block, return value determines to spawn a new block or not
	if(gameOver && cmd != "restart") return;

	Block * currentBlock = blocks->at((blocks->size() - 2));
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
		checkClear();
		Block * next = randBlock->getBlock();
		if(next != NULL){
			blocks->push_back(next);
			(blocks->at((blocks->size() - 2)))->activate(board);
			board->XwindowUpdate(blocks->at(blocks->size()-1)->getOutput(), blocks->at(blocks->size()-1)->getColour());
		}else{
			gameOver = true;
            board->XwindowUpdate("Game Over", 1);
		}
	}else if(cmd == "levelup"){
	    level = randBlock->levelUp();
	    board->XwindowUpdate(level, score, highScore);
	}else if(cmd == "leveldown"){
	    level = randBlock->levelDown();
	    board->XwindowUpdate(level, score, highScore);
	}else if(cmd == "restart"){
	    gameOver = false;
		score = 0;
		level = initLevel;
		board->reset();
		board->XwindowUpdate(level, score, highScore);
		randBlock->setLevel(level);
		for(vector<Block *>::iterator vi=blocks->begin();vi!=blocks->end();++vi){
		//using iterators to delete all the block pointers in Blocks
			delete *vi;
		}
		blocks->clear();
		blocks->push_back(randBlock->getBlock());
		blocks->push_back(randBlock->getBlock());
		board->XwindowUpdate(blocks->at(1)->getOutput(), blocks->at(1)->getColour());
		(blocks->at(0))->activate(board);
	}else{
		cerr << "BAD COMMAND" << endl;
	}
}
void Game::checkClear(){
	int linesCleared = 0;
	int blockScore = 0;
	int score = 0;
	bool rowFilled = false;
	Cell * temp;
	for(int i=(board->getRow()-1);i>0;i--){
		rowFilled = true;
		for(int j=0;j<board->getColumn();j++){
			rowFilled = rowFilled && ((board->getCell(i,j))->getType() != ' ');
		}
		if(rowFilled){
			linesCleared++;
			for(int j=0;j<board->getColumn();j++){
				(board->getCell(i,j))->notifyBlock();
				(board->getCell(i,j))->setType(' ');
				//doing so notifies the corresponding block

			}
			board->findTop();
			for(int k=i;k>=board->getTop();k--){
			//moves all the blocks down
			//draws the top one before the bottom one
				for(int j=0;j<board->getColumn();j++){
						temp = board->getCell(k,j);
						board->setCell(board->getCell(k-1,j), k, j);
						board->setCell(temp, k-1, j);
						(board->getCell(k,j))->setCoords(k,j);
						(board->getCell(k-1,j))->setCoords(k-1,j);
						board->XwindowUpdate(board->getCell(k-1,j));
						board->XwindowUpdate(board->getCell(k,j));
				}
			}
		}
	}
	for(vector<Block *>::iterator vi=blocks->begin();vi!=blocks->end();vi++){
		if((*vi)->getStatus() == 0){

			blockScore = blockScore + (int)pow((((*vi)->getLevel() + 1) * 1.0), 2);
			delete *vi;
			vi = blocks->erase(vi);
		}
	}
	score = (int)pow(((linesCleared + level)* 1.0), 2) + blockScore;
	updateScore(score);
}

ostream& operator<<(ostream& out, const Game& g){
	if(!g.gameOver){
		out << "Level:" << setw(spacing + 3) << g.level << endl;
		out << "Score:" << setw(spacing + 3) << g.score << endl;
		out << "Hi Score:" << setw(spacing) << g.highScore << endl;
		out << "----------" << endl;
		out << *(g.board);
		out << "----------" << endl;
		out << "Next:" << endl;
		out << *(g.blocks->at((g.blocks->size() - 1))) << endl;
		return out;
	}else{
		out << "Game Over" <<endl;
		return out;
	}
}
