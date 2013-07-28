#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cell.h"
#include <string>

static const int tetris = 4;
class Block {
    char type;					//which type of block is it
	Cell * parts[tetris];			//the four parts of a tetric block
	int colour;				//colour of the blocks
	int alive;				//count of number of alive cells; starts at 4
	std::string output;
	void initCells();
public:
	Block(const char& type=0, const int& colour=0, const std::string& str=0, Cell* parts[]=0);
	~Block();
    void rotate(Board* board, const bool&);	//parameter determines clockwise or counterclockwise rotation
	void shift(Board* board, const int&);	//paramenter indicates which direction of motion
	void notify();				//notifies the board
	friend std::ostream& operator<<(std::ostream&, const Block&);
};

#endif
