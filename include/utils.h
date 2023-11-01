#ifndef UTILS_H
#define UTILS_H

#include <vector>

#include "Grid.h"


inline bool isValidCell(int x, int y, const Grid& grid) 
{
    return (x >= 0 && x < grid.getNumRows() && y >= 0 && y < grid.getNumColumns());
}

#endif