#include "Grid.h"
#include "utils.h"


Grid::Grid() : numRows(80), numColumns(80) 
{
    // Initialize the grid with the specified number of rows and columns
    cells.resize(numRows, std::vector<bool>(numColumns, false));
}


Grid::Grid(int numRows, int numColumns) : numRows(numRows), numColumns(numColumns) 
{
    // Initialize the grid with the specified number of rows and columns
    cells.resize(numRows, std::vector<bool>(numColumns, false));
}

std::vector<Node> Grid::getNeighborCells(const Node& node) const 
{
    std::vector<Node> neighbor_cells;
    const int curr_x = node.x;
    const int curr_y = node.y;

    // movements from current node to neighbor ones in 2D vector. Includes (up, down, left, right, diagonals)
    const int movements[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, // up, down, left, right
                                 {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}; // diagonals

    // for all neighbor movements
    for(int i = 0; i < 8; i++) 
    {
        int newX = curr_x + movements[i][0];
        int newY = curr_y + movements[i][1];

        // if new movement is within the grid bounds and not blocked
        if(isValidCell(newX, newY) && !isBlocked(newX, newY))
        {
            Node neighbor = {newX, newY, 0, 0, 0, nullptr};
            neighbor_cells.push_back(neighbor);
        }
    }

    return neighbor_cells;
}

bool Grid::isCellBlocked(int row, int col) const 
{
    // Check if the provided cell is within bounds
    if(isValidCell(row, col, *this)) 
    {
        return cells[row][col];
    }

    // out of grid cells are considered blocked
    return true;
}

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