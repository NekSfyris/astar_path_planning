#ifndef GRID_H
#define GRID_H

#include <vector>
#include <memory>

#include "Cell.h"
#include "utils.h"


class Grid {
public:
    Grid(); // default Constructor
    Grid(int numRows, int numColumns); // Constructor
    std::vector<Node> getNeighborCells(const Node& node) const; // get all neighbours of current node
    std::vector<Node> getNeighborCells(const Node* node) const; // get all neighbours of current node
    std::vector<Node> getNeighborCells(std::shared_ptr<Node> node) const; // get all neighbours of current node
    bool isCellBlocked(int row, int col) const; // check if cell is blocked
    void setCellBlocked(int row, int col); // set status of cell to blocked
    std::vector<std::vector<bool>> cells; // 2D grid
    int getNumRows() const; // get number of rows in 2D grid
    int getNumColumns() const; // get number of cols in 2D grid
 
    int numRows;
    int numColumns;
    
private:

};

#endif