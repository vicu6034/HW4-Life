#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Cell;

class CellMap {
public:
    CellMap();

    void Step();

    std::vector<Cell*> get_neighbors(int index);
    Cell * get_cell(int index) { return cells_[index]; }

    double get_percent_alive();

    static const int NUM_CELLS = 200;

private:
    Cell *cells_[NUM_CELLS];
};

#endif // CELLMAP_H
