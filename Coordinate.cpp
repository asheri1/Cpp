#include "Coordinate.h"


Coordinate::Coordinate(int x, int y): xValue(x), yValue(y) {}

int Coordinate::getX() const {return xValue;}
int Coordinate::getY() const {return yValue;}

void Coordinate::setX(int x) { this->xValue = x; }
void Coordinate::setY(int y) { this->yValue = y; }


// equality operator
bool Coordinate::operator==(const Coordinate& other) const {
    return (xValue == other.getX() && yValue == other.getY());
}