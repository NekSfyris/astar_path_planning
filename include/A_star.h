#ifndef ASTAR_H
#define ASTAR_H

#include "Grid.h"
#include "Cell.h"

#include <vector>

class AStar {
public:
    AStar();
    std::vector<Cell> findPath(const Grid& grid, const Cell& start, const Cell& goal);
private:

};

#endif