#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include <iostream>

#include "utils.h"

using namespace std;


class Cell {
public:
    Cell();
    Cell(int row, int col, int numRows, int numColumns);
    int getRow() const;
    int getCol() const;
private:
    int row;
    int col;
};

#endif