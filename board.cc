#include "board.h"
using namespace std;

	Cell ** gameBoard;		//the board object that holds the game matrix
	Xwindow * window;		//the GUI
	int xStartPos;			//default starting location for the blocks
	int yStartPos;
	int column;				//column of the matrix
	int row;				//row of the matrix
	int cellSize;
	public:
Board()
:gameBoard(NULL),window(NULL),xStartPos(0),yStartPos(0),column(0),row(0){}

Board(const int& row, const int& column, const int& xStart, const int& yStart)
:xStartPos(xStart),yStartPos(yStart),column(column),row(row){
	gameBoard = new * Cell[row];
	for(int i=0;i<row;i++){
		gameBoard[row] = new Cell[column];
	}
	window = new Xwindow(row*cellSize, column*cellSize);
}

~Board(){
	for(int i=0;i<row;i++){
		delete [] gameBoard[row];
	}
	delete [] gameBoard;
	delete window;
}

bool isEmpty(const int&x , const int&y){	//returns if the location is empty, false if it reaches an edge
	if(x < 0 || x >= row) return false;
	if(y < 0 || y >= column) return false;
	if(gameBoard[x][y].getType() == ' ') return true;
	return false;
}

void moveCell(const int& xFrom, const int& yFrom, const int& xDest, const int& yDest){
//moves the cell, empties the original cell, invoked by the Block class
	if(x < 0 || x >= row) return false;
	if(y < 0 || y >= column) return false;
	if(gameBoard[x][y].getType() != ' ') return false;
	gameBoard[xDest][yDest].setType(gameBoard[xFrom][yFrom].getType());
	return true;
}
void XwindowUpdate();						//updates the window

ostream& operator<<(ostream& out, const Board& b){
	for(int i=0;i<row;i++){
		for(int j=0;j<column;j++){
			out << b.gameBoard[i][j];
		}
	}
	return out;
}
