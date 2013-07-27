#include "board.h"
using namespace std;


Board::Board(const int& row, const int& column, const int& xStart, const int& yStart)
:xStartPos(xStart),yStartPos(yStart),column(column),row(row){
	gameBoard = new Cell * [row];
	for(int i=0;i<row;i++){
		gameBoard[row] = new Cell[column];
	}
	window = new Xwindow(row*cellSize, column*cellSize);
}

Board::~Board(){
	for(int i=0;i<row;i++){
		delete [] gameBoard[row];
	}
	delete [] gameBoard;
	delete window;
}

bool Board::isEmpty(const int&x , const int&y){	
//returns if the location is empty, false if it reaches an edge
	if(x < 0 || x >= row) return false;
	if(y < 0 || y >= column) return false;
	if(gameBoard[x][y].getType() == ' ') return true;
	return false;
}

void Board::moveCell(const int& xFrom, const int& yFrom, const int& xDest, const int& yDest){
//moves the cell, empties the original cell, invoked by the Block class
//ensures that the 2 set of coordinates is valid
	if(gameBoard[xDest][yDest].getType() != ' ') return;
	gameBoard[xDest][yDest].setType(gameBoard[xFrom][yFrom].getType());
}
Cell * Board::getCell(const int& x, const int& y){
	if (x < 0 || x >= row) return 0;
	if (y < 0 || y >= column) return 0;
	return &(gameBoard[x][y]);
}

void Board::XwindowUpdate(Cell* c){
	
	
	
	
}						//updates the window

ostream& operator<<(ostream& out, const Board& b){
	for(int i=0;i<b.row;i++){
		for(int j=0;j<b.column;j++){
			out << b.gameBoard[i][j];
		}
	}
	return out;
}
