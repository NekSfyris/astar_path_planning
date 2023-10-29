#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include <iostream>

#include "Grid.h"

using namespace std;


class Cell {
public:
    Cell();
    Cell(int x, int y, const Grid& grid);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
};

#endif