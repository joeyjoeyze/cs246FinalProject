#ifndef __CELL_H__
#define __CELL_H__
#include<iostream>

class Block;
class Cell{
    char type;					//which type is the cell in
	int x;						//x, y coordinates on the matrix
	int y;
	int colour;				//colour value for Xwindow
	bool changed;				//was there a change in the cell
	Block * block;				//pointer to the block where the cell belongs to
 public:
	Cell();
	~Cell();
    void setCoords(const int&, const int&);		//set function for location
	void setType(const char&);					//changes the cell's letter
	void setBlock(Block *);						//sets the block of cell
	char getType();								//returns the type character
	int getX();									//returns x coordinate
	int getY();									//returns y coordinate
	int getColour();								//returns colour
	friend std::ostream& operator<<(std::ostream&, const Cell&);
};

#endif
