#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();
    Cell(int x, int y);
    int getX() const;
    int getY() const;
private:
    int x;
    int y;
};

#endif