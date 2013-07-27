#include "game.h"
using namespace std;

Game::Game(const int& level=0, bool GUI=true)
:score(0),level(level),initialLevel(level),highScore(0),inFile(NULL){
	board = new Board;

}

Game::Game(const String& fileName, const int& level=0, bool GUI=true)
:score(0),level(level),initialLevel(level),highScore(0){
	inFile->open(fileName.c_str());
	board = new Board;
	
}

Game::~Game(){
	delete board;
}

void updateScore(const int& newScore){	//called when a row is cancelled, could implement without parameter
	if(newScore > highScore) highScore = newScore;
	score = newScore;
}

bool Game:command(const string& cmd){	//finds and calls the command from main in block, return value determines to spawn a new block or not
	
}

void Game::restart(){
	score = 0;
	level = 0;
	highScore = 0;
	delete board;
	board = new Board;
	
}



ostream& operator<<(ostream& out, const Game& g){
		out << "Level:\t\t" << g.level << endl;
		out << "Score:\t\t" << g.score << endl;
		out << "Hi Score:\t" << g.highScore << endl;
		out << "----------" << endl;
		out << g.board << endl;
		out << "----------" << endl;
		out << g.nextBlock << endl;
		return out;
	}
