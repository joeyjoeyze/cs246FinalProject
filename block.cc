#include "block.h"

Block::Block(Board* board, char type, Cell *parts[]):
  board(board), type(type), alive(4){
    for (int i=0; i<tetris; ++i)
        this->parts[i] = parts[i];
}
Block::~Block(){
    delete[] parts;
}

void Block::rotate(bool direction){
    //0 for ccw
    //1 for cw
    int topX=99;
    int leftY=99;
    int botX=-1;
    int rightY=-1;

    for (int i=0; i<tetris; ++i){
        if (parts[i]->getX() < topX) topX = parts[i]->getX();
        if (parts[i]->getY() < leftY) leftY = parts[i]->getY();
        if (parts[i]->getX() > botX) botX = parts[i]->getX();
        if (parts[i]->getY() > rightY) rightY = parts[i]->getY();
    }

    Cell *newParts[tetris];

    for (int i=0; i<tetris; ++i){
        int x = parts[i]->getX();
        int y = parts[i]->getY();

        int tmp = x;
        x = botX - (y - leftY);         //first flip the block diagonally, top-left to bottom-right.
        y = botX - tmp + leftY;

        if (direction == false)                         //ccw
            y = leftY + botX-topX - (y-leftY)           //flip horizontally
        else if (direction)                             //cw
            x = bottomX - (rightY-leftY -(bottomX-x));  //flip vertically
        newParts[i] = board->getCell(x,y);
        if (newParts[i] == 0) return;
    }

    for (int i=0; i<tetris; ++i){
        if (newParts[i]->getType()==' ') continue;      //if empty

        bool cont = false;
        for (int j=0; j<tetris; ++j){
            if (newParts[i]==parts[j]){                 //if cell in current block
                cont = true;
                break;
            }
        }
        if (cont) continue;

        return;
    }

    for (int i=0; i<tetris; ++i)
        parts[i]->setType(' ');

    for (int i=0; i<tetris; ++i){
        newParts[i]->setType(type);
        newParts[i]->setBlock(*this);
        parts[i] = newParts[i];
    }
}
void Block::shift(const int& direction){
    //0 down
    //1 left
    //2 right
    Cell *newParts[tetris];

    for (int i=0; i<tetris; ++i){
        int x = parts[i]->getX();
        int y = parts[i]->getY();

        if (direction == 0)
            newParts[i] = board->getCell(x+1, y);       //down
        else if (direction == 1)
            newParts[i] = board->getCell(x, y-1);       //left
        else if (direction == 2)
            newParts[i] = board->getCell(x, y+1);       //right

        if (newParts[i]==0) return;
    }

    for (int i=0; i<tetris; ++i){
        if (newParts[i]->getType()==' ') continue;

        bool cont = false;
        for (int j=0; j<tetris; ++j){
            if (newParts[i]==parts[j]){
                cont = true;
                break;
            }
        }
        if (cont) continue;

        return;
    }

    for (int i=0; i<tetris; ++i)
        parts[i]->setType(' ');

    for (int i=0; i<tetris; ++i){
        newParts[i]->setType(type);
        newParts[i]->setBlock(*this);
        parts[i] = newParts[i];
    }
}

void Block::notify() {
    alive--;
    if (alive==0){

    }
}
