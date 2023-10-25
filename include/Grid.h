#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {
public:
    Grid();
    Grid(int numRows, int numColumns);
    bool isCellBlocked(int row, int col) const; // Check if a cell is blocked
    void setCellBlocked(int row, int col); // Set the status of a cell
private:
    std::vector<std::vector<bool>> cells; //2D grid
    int numRows;
    int numColumns;
};

#endif