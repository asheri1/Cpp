#include "Coordinates.h"

Coordinates::Coordinates(int x, int y): xValue(x), yValue(y) {}

int Coordinates::getX() const {return xValue;}
int Coordinates::getY() const {return yValue;}

Coordinates Coordinates::getCoordinatesN() const{
    return Coordinates(xValue, yValue-1);
}

Coordinates Coordinates::getCoordinatesE() const{
    return Coordinates(xValue+1, yValue);
}

Coordinates Coordinates::getCoordinatesS() const{
    return Coordinates(xValue, yValue+1);
}

Coordinates Coordinates::getCoordinatesW() const{
    return Coordinates(xValue-1, yValue);
}


// void Coordinates::setX(int x) { this->xValue = x; }
// void Coordinates::setY(int y) { this->yValue = y; }


// equality operator
bool Coordinates::operator==(const Coordinates& other) const {
    return (xValue == other.getX() && yValue == other.getY());
}

