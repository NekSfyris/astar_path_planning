#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include <iostream>

#include "Grid.h"

using namespace std;


class Cell {
public:
    Cell();
    Cell(int row, int col, const Grid& grid);
    int getRow() const;
    int getCol() const;
private:
    int row;
    int col;
};

#endif