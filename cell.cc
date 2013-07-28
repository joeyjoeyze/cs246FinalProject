#include "cell.h"

Cell::Cell():type(' '),x(0),y(0),colour(1),changed(false),block(NULL){}

Cell::~Cell(){}

void Cell::setCoords(const int& x, const int& y){		//set function for location
	this->x = x;
	this->y = y;
}

void Cell::setType(const char& type){				//changes the cell's letter
	if(type == ' '){
		block->notify();
		block = NULL;
		colour = 1;
	}
	this->type = type;
}

void Cell::setBlock(Block * block){
	this->block = block;
}

void Cell::setColour(const int& c){
	colour = c;
}

char Cell::getType(){		//returns the type character
	return type;
}
int Cell::getX(){
	return x;
}
int Cell::getY(){
	return y;
}

int Cell::getColour(){
	return colour;
}
	
std::ostream& operator<<(std::ostream& out, const Cell& c){
	out << c.type;
	return out;
}



