#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
private:
    int xValue;
    int yValue;

public:
    // constructor
    Coordinate(int x, int y);

    // getters
    int getX() const;
    int getY() const;

    // setters
    void setX(int x);
    void setY(int y);

    // equality operator
    bool operator==(const Coordinate& other) const;

};

#endif 
