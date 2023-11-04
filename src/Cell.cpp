#include "Cell.h"


// Default Constructor
Cell::Cell() : row(0), col(0) 
{
}

// Constructor
Cell::Cell(int row, int col, int numRows, int numColumns)
{
    // Check if the point is within the valid range of the grid
    if(isValidCell(row, col, numRows, numColumns)) 
    {
        this->row = row;
        this->col = col;
    } 
    else 
    {
        std::cerr << "Invalid point coordinates: (" << row << ", " << col << "). Exiting." << std::endl;
        exit(1); // Terminate
    }
}

// Get row coordinate of 2D grid
int Cell::getRow() const 
{
    return row;
}

// Get col coordinate of 2D grid
int Cell::getCol() const 
{
    return col;
}