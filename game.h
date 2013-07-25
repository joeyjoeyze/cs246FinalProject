#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include "block.h"
#include "window.h"
#include "board.h"

class Game{
	int score;				//score of the current game, implement this in player for multiplayer
	Board * board;			//the board object that holds the game matrix
	Block block;			//the current block used by the player
	public:
	Game();
	~Game();
	Block nextBlock();				//randomly generates a block
	void updateScore(const int&);	//called when a row is cancelled, could implement without parameter
	bool command(const std::string&);	//finds and calls the command from main in block, return value determines to spawn a new block or not
	friend std::ostream& operator<<(std::ostream&, const Game&);
};

#endif
