#include "Grid.h"
#include "utils.h"

// Default Constractor
Grid::Grid() : numRows(80), numColumns(80) 
{
    // Initialize the grid with the specified number of rows and columns
    cells.resize(numRows, std::vector<bool>(numColumns, false));
}

// Constractor
Grid::Grid(int numRows, int numColumns) : numRows(numRows), numColumns(numColumns) 
{
    // Initialize the grid with the specified number of rows and columns
    cells.resize(numRows, std::vector<bool>(numColumns, false));
}

bool Grid::isCellBlocked(int row, int col) const 
{
    // Check if the provided cell is within bounds
    if(isValidCell(row, col, *this)) 
    {
        return cells[row][col];
    }

    return true; // Consider out-of-bounds cells as blocked
}

// Set the status of a cell as blocked (true) or unblocked (false)
void Grid::setCellBlocked(int row, int col) 
{
    // Check if the provided cell is within bounds
    if(isValidCell(row, col, *this)) 
    {
        cells[row][col] = true;
    }
}

int Grid::getNumRows() const 
{
    return numRows;
}

int Grid::getNumColumns() const 
{
    return numColumns;
}