#ifndef CELL_H
#define CELL_H

#include "Grid.h"
#include "Point.h"

#include <vector>

class AStar {
public:
    AStar();
    std::vector<Point> findPath(const Grid& grid, const Cell& start, const Cell& goal);
private:

};

#endif