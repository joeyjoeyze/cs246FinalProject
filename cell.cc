#include "cell.h"
#include "block.h"

Cell::Cell():type(' '),x(0),y(0),changed(false),block(NULL){}
/*
Cell::Cell(const char& type, const int& x, const int& y)
:type(type),x(x),y(y),changed(false){}
*/
Cell::~Cell(){}

void Cell::setCoords(const int& x, const int& y){		//set function for location
	this->x = x;
	this->y = y;
}

void Cell::setType(const char& type){				//changes the cell's letter
	if(type == ' '){
		block->notify();
		block = NULL;
	}
	this->type = type;
}

void Cell::setBlock(Block * block){
	this->block = block;
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
	
std::ostream& operator<<(std::ostream& out, const Cell& c){
	out << c.type;
	return out;
}



