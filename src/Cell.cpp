#include "Cell.h"

// Default Constructor
Cell::Cell() : x(0), y(0) 
{
}

// Constructor
Cell::Cell(int x, int y) : x(x), y(y) 
{
}

// Get x coordinate of 2D grid
int Cell::getX() const 
{
    return x;
}

// Get y coordinate of 2D grid
int Cell::getY() const 
{
    return y;
}