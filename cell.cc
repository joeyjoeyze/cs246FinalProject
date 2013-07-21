#include "cell.h"

Cell::Cell():type(' '),x(0),y(0),changed(false){}
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
	this->type = type;
}

char Cell::getType(){		//returns the type character
	return type;
}
	
std::ostream& operator<<(std::ostream& out, const Cell& c){
	out << c.type;
	return out;
}



