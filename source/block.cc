#include "block.h"

using namespace std;

Block::Block(const char& type, const int& colour, const string& str, Cell* parts[]):
  type(type), colour(colour), alive(4), level(0), output(str){
	for (int i=0; i<tetris && parts; ++i){
        this->parts[i] = parts[i];
	}
}

Block::Block(const Block& other):
  type(other.type), colour(other.colour), alive(other.alive), level(0), output(other.output){
    for (int i=0; i<tetris; ++i){
        parts[i] = other.parts[i];
	}
}
Block Block::operator=(const Block& other){
	Block temp = other;
	swap(temp);
	return *this;
}
void Block::swap(Block& other){
	char typetmp = type;
	type = other.type;
	other.type = typetmp;

	Cell * partstmp;
	for(int i=0;i<tetris;i++){
		partstmp = parts[i];
		parts[i] = other.parts[i];
		other.parts[i] = partstmp;
	}

	int colourtmp = colour;
	colour = other.colour;
	other.colour = colourtmp;

	int alivetmp = alive;
	alive = other.alive;
	other.alive = alivetmp;

	string outputtmp = output;
	output = other.output;
	other.output = outputtmp;
}

Block::~Block(){
    //delete[] parts;
}

void Block::activate(Board * board){
    for (int i=0; i<tetris; ++i){
        parts[i]->setType(type);
        parts[i]->setBlock(this);
        parts[i]->setColour(colour);
        board->XwindowUpdate(parts[i]);
    }
}

void Block::rotate(Board* board, const bool& direction){
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

        if (direction == false)         //ccw
            y = leftY + botX-topX - (y-leftY);     //flip horizontally within the width of the rectangle encaspulating
        else if (direction)             //cw
            x = botX - (rightY-leftY -(botX-x));
        newParts[i] = board->getCell(x,y);
        if (newParts[i] == 0) return;
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

    for (int i=0; i<tetris; ++i){
        parts[i]->setType(' ');
        board->XwindowUpdate(parts[i]);
    }

    for (int i=0; i<tetris; ++i){
        newParts[i]->setType(type);
        newParts[i]->setBlock(this);
        newParts[i]->setColour(colour);
        board->XwindowUpdate(newParts[i]);
        parts[i] = newParts[i];
    }
}
void Block::shift(Board* board, const int& direction){
    //0 down
    //1 left
    //2 right
    Cell *newParts[tetris];

    for (int i=0; i<tetris; ++i){
        int x = parts[i]->getX();
        int y = parts[i]->getY();

        if (direction == 0)
            newParts[i] = board->getCell(x+1, y);
        else if (direction == 1)
            newParts[i] = board->getCell(x, y-1);
        else if (direction == 2)
            newParts[i] = board->getCell(x, y+1);

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

    for (int i=0; i<tetris; ++i){
        parts[i]->setType(' ');
        board->XwindowUpdate(parts[i]);
    }

    for (int i=0; i<tetris; ++i){
        newParts[i]->setType(type);
        newParts[i]->setBlock(this);
        newParts[i]->setColour(colour);
        board->XwindowUpdate(newParts[i]);
        parts[i] = newParts[i];
    }
}

char Block::getType(){
    return type;
}

string Block::getOutput(){
    return output;
}

int Block::getColour(){
    return colour;
}

int Block::getStatus(){
	return alive;
}

int Block::getLevel(){
	return level;
}

Cell* Block::getPart(const int& index){
	return parts[index];
}

void Block::setLevel(const int& level){
	this->level = level;
}

void Block::notify() {
    alive--;
}

ostream& operator<<(ostream& out, const Block& b){
	out << b.output;
	return out;
}
