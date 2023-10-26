#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>

#include "Grid.h"
#include "Cell.h"

#include <vector>

using namespace std;

class AStar {
public:
    AStar();
    std::vector<Cell> findPath(const Grid& grid, const Cell& start, const Cell& goal);
private:

};

#endif