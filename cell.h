#ifndef __CELL_H__
#define __CELL_H__
#include<iostream>

class Cell{
    char type;					//which type is the cell in
	int x;						//x, y coordinates on the matrix
	int y;
	bool changed;				//was there a change in the cell
 public:
	Cell();
	~Cell();
    void setCoords(const int&, const int&);		//set function for location
	void setType(const char&);				//changes the cell's letter
	char getType();								//returns the type character
	friend std::ostream& operator<<(std::ostream&, const Cell&);
};

#endif
