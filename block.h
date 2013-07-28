#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cell.h"
#include "board.h"

static const int tetris = 4;
class Block {
    char type;					//which type of block is it
	Cell * parts[tetris];			//the four parts of a tetric block
	int colour;				//colour of the blocks
	int alive;				//count of number of alive cells; starts at 4
								//need some transformation parameters
 public:
	Block::Block(Board* board=0, char type=0, int colour=0, Cell *parts[]=0); //non-virtual ctor & dtor
	~Block();
    	void rotate(Board* board, const bool&);	//parameter determines clockwise or counterclockwise rotation
	void shift(Board* board, const int&);	//paramenter indicates which direction of motion
	void notify();				//notifies the board
	friend std::ostream& operator<<(std::ostream&, const Block&);
};

#endif
