#ifndef __BOARD_H__
#define __BOARD_H__
#include "cell.h"
#include "window.h"
#include <iostream>
#include <sstream>

static const char empty = ' ';
static const int cellSize = 30;					//size of each cell on screen
class Board{
	Cell *** gameBoard;							//the board object that holds the game matrix
	Xwindow * window;							//the GUI
	int xStartPos;								//default starting location for the blocks
	int yStartPos;
	int column;									//column of the matrix
	int row;									//row of the matrix
	int top;									//highest row where a cell is non-empty
	bool GUI;
	public:
	Board(const int& row=0, const int& column=0, const int& xStart=3, const int& yStart=0, bool GUI=true);
	~Board();
	bool isEmpty(const int&x , const int&y);	//returns if the location is empty, false if it reaches an edge
	void reset();
	void findTop();

	void XwindowUpdate(std::string output, int colour);     //for drawing next block
	void XwindowUpdate(Cell* c);	            			//updates the cell of the window
	void XwindowUpdate(int level, int score, int highscore);	//updates the text of the window
	
	Cell * getCell(const int& x, const int&y);
	void setCell(Cell *, const int&,const int&);
	int getRow();
	int getColumn();
	int getTop();
	friend std::ostream& operator<<(std::ostream&, const Board&);
};

#endif

