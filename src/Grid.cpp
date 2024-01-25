#include "Grid.h"


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


std::vector<Node> Grid::getNeighborCells(std::shared_ptr<Node> node) const
{
    std::vector<Node> neighbor_cells;
    const int curr_x = node->row;
    const int curr_y = node->col;

    // movements from current node to neighbor ones in 2D vector. Includes (up, down, left, right, diagonals)
    const int movements[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, // up, down, left, right
                                 {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}; // diagonals

    // for all neighbor movements
    for(int i = 0; i < 8; i++) 
    {
        int newX = curr_x + movements[i][0];
        int newY = curr_y + movements[i][1];

        // if new movement is within the grid bounds and not blocked
        if(isValidCell(newX, newY, numRows, numColumns) && !isCellBlocked(newX, newY))
        {
            Grid grid;

            // Cell curr_node(node->row,  node->col, numRows, numColumns);
            Node startNode = {grid.startCell.row, grid.startCell.col, 0, 0, nullptr};
            Node goalNode = {grid.goalCell.row, grid.goalCell.col, 0, 0, nullptr};

            Node neighbor = {newX, newY, calcCostEuclidean(startNode, node), calcHeuristicEuclidean(node, goalNode), nullptr};
            neighbor_cells.push_back(neighbor);
            // std::shared_ptr<Node> neighbor = std::make_shared<Node>(newX, newY, 0, 0, nullptr);
            // neighbor_cells.push_back(neighbor);
        }
    }

    return neighbor_cells;
}



bool Grid::isCellBlocked(int row, int col) const 
{
    // Check if the provided cell is within bounds
    if(isValidCell(row, col, numRows, numColumns)) 
    {
        return cells[row][col];
    }

    // out of grid cells are considered blocked
    return true;
}

void Grid::setCellBlocked(int row, int col) 
{
    // Check if the provided cell is within bounds
    // if(isValidCell(row, col, *this))
    if(isValidCell(row, col, numRows, numColumns)) 
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