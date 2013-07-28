#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cell.h"
#include "board.h"
#include <string>

static const int tetris = 4;
class Block {
    char type;					//which type of block is it
	Cell * parts[tetris];			//the four parts of a tetric block
	int colour;				//colour of the blocks
	int alive;				//count of number of alive cells; starts at 4
	std::string output;
	void swap(Block&);
	void initCells();
public:
	Block(const char& type=0, const int& colour=0, const std::string& str="", Cell* parts[]=0);
	Block(const Block& other);
	Block operator=(const Block&);
	~Block();
	void activate(Board *);			//notifies the cells it contains of the block's existence
    void rotate(Board* board, const bool&);	//parameter determines clockwise or counterclockwise rotation
	void shift(Board* board, const int&);	//paramenter indicates which direction of motion
	char getType();                 //returns type
	std::string getOutput();             //returns output
	int getColour();                    //returns colour
	void notify();				//notifies the board
	friend std::ostream& operator<<(std::ostream&, const Block&);
};

#endif
