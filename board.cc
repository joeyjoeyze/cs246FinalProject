#include "board.h"
using namespace std;

Board::Board(const int& row, const int& column, const int& xStart, const int& yStart, bool GUI)
:xStartPos(xStart),yStartPos(yStart),column(column),row(row),GUI(GUI){
	gameBoard = new Cell * [row];
	for(int i=0;i<row;i++){
		gameBoard[i] = new Cell[column];
		for (int j=0; j<column; j++)
            gameBoard[i][j].setCoords(i,j);
	}
	if(GUI){
		window = new Xwindow(column*cellSize, 50+(3+row)*cellSize);  //50 for score, 3 for next block
		window->fillRectangle(0,0, column*cellSize, 50+(3+row)*cellSize);

	}else {
		window = NULL;
	}
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

void Board::XwindowUpdate(string output, int colour){  //this is for drawing next block.
    window->fillRectangle(0,50+row*cellSize,column*cellSize, 3*cellSize);

    int x = 3 * cellSize;
    int y = 50 + cellSize*row + cellSize/2;

    window->drawString(5, y+cellSize, "Next block:", 0);

    for (int i=0; i<output.length(); ++i){
        if (output[i]=='\n'){
            x = 2 * cellSize;
            y += cellSize;
        } else if (output[i]!=' ')
            window->fillRectangle(x+1,y+1,cellSize-1, cellSize-1, colour);
        x += cellSize;
    }
}

void Board::XwindowUpdate(Cell* c){
	if (window==0) return;
    window->fillRectangle(c->getY()*cellSize+1, c->getX()*cellSize+51, cellSize-2, cellSize-2, c->getColour());
}						//window update cell

void Board::XwindowUpdate(int level, int score, int highscore){
	if (window==0) return;
    window->fillRectangle(0, 0, column*cellSize, 50, 1);
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
		out << endl;
	}
	return out;
}
