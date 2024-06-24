#include "Coordinates.h"

Coordinates::Coordinates(int x, int y): xValue(x), yValue(y) {}

int Coordinates::getX() const {return xValue;}
int Coordinates::getY() const {return yValue;}

void Coordinates::setX(int x) { this->xValue = x; }
void Coordinates::setY(int y) { this->yValue = y; }


// equality operator
bool Coordinates::operator==(const Coordinates& other) const {
    return (xValue == other.getX() && yValue == other.getY());
}