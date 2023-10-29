#include "Cell.h"

// Default Constructor
Cell::Cell() : x(0), y(0) 
{
}

// Constructor
Cell::Cell(int x, int y, const Grid& grid)
{
    // Check if the point is within the valid range of the grid
    if (x >= 0 && x < grid.getNumRows() && y >= 0 && y < grid.getNumColumns()) 
    {
        this->x = x;
        this->y = y;
    } 
    else 
    {
        std::cerr << "Invalid point coordinates: (" << x << ", " << y << "). Exiting." << std::endl;
        exit(1); // Terminate
    }
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