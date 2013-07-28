#ifndef __GAME_H__
#define __GAME_H__
#include<vector>
#include<string>
#include<iostream>
#include<iomanip>
class RandomBlock;
class Block;
class Board;
static const int spacing = 4;			//padding spacing to right align text
class Game{
	int score;							//score of the current game, implement this in player for multiplayer
	int level;							//the current level of the game;
	int highScore;						//current high score
	int initLevel;						//initial level stated on the command line if non-zero
	bool GUI;
	std::vector<Block *> * blocks;		//the vector of blocks
	RandomBlock * randBlock;
	Board * board;						//the board object that holds the game matrix
  public:
	Game(const int& level=0, bool GUI=true);
	Game(const std::string& fileName, const int& level=0, bool GUI=true);
	~Game();
	void updateScore(const int&);		//called when a row is cancelled, could implement without parameter
	void command(const std::string&);	//finds and calls the command from main in block, return value determines to spawn a new block or not
	friend std::ostream& operator<<(std::ostream&, const Game&);
};

#endif
