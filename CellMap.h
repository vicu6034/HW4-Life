#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Cell;

class CellMap {
public:
    // Default constructor
    CellMap();

    // Get a cell by indec
    Cell * get_cell(int index) { return cells_[index]; }
    // Get percent of alive cells
    double get_percent_alive();

    // Method to determine the next cell map
    void Step();
    // Method to find all the neighbors of a cell
    std::vector<Cell*> get_neighbors(int index);

    static const int NUM_CELLS = 200;

private:
    Cell *cells_[NUM_CELLS];
};

#endif // CELLMAP_H
