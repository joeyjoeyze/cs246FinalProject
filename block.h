#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cell.h"
#include "board.h"

static const int tetris = 4;
class Block {
    char type;					//which type of block is it
	Cell * parts[tetris];			//the four parts of a tetric block
	Board * board;				//need this to invoke the moveCell command in board
	int alive;				//count of number of alive cells; starts at 4
								//need some transformation parameters
 public:
	Block();					//non-virtual ctor & dtor
	~Block();
    	void rotate(bool);		//parameter determines clockwise or counterclockwise rotation
	void shift(const int&);		//paramenter indicates which direction of motion
	bool canMove();			//determines if the block is able to move at its current location
	void notify();			//notifies the board
};

#endif
