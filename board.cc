#include "board.h"
using namespace std;


Board::Board(const int& row, const int& column, const int& xStart, const int& yStart)
:xStartPos(xStart),yStartPos(yStart),column(column),row(row){
	gameBoard = new Cell * [row];
	for(int i=0;i<row;i++){
		gameBoard[row] = new Cell[column];
	}
	window = new Xwindow(column*cellSize, 50+(3+row)*cellSize);  //100 for score, 3 for next block
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
    window->fillRectangle(c->getY()*cellSize+1, c->getX()*cellSize+51, cellSize-2, cellSize-2, c->getColour());
}						//window update cell

void Board::XwindowUpdate(int level, int score, int highscore){
    window->fillRectangle(0, 0, column*cellSize, 50, 1)
    stringstream ss;
    ss << "Level:       " << level;
    window->drawString(50, 10, ss.str(), 0);

    ss.str(string());
    ss << "Score:       " << score;
    window->drawString(50, 20, ss.str(), 0);

    ss.str(string());
    ss << "High score:  " << highscore;
    window->drawString(50, 30, ss.str(), 0);
}                       //window update text

ostream& operator<<(ostream& out, const Board& b){
	for(int i=0;i<b.row;i++){
		for(int j=0;j<b.column;j++){
			out << b.gameBoard[i][j];
		}
	}
	return out;
}
