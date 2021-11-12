#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Cell;
class GraphBar;

class CellMap {
public:
    // Default constructor
    CellMap();

    // Get a cell by indec
    Cell * get_cell(int index) { return cells_[index]; }
    // Get percent of alive cells
    int get_percent_alive();

    // Method to determine the next cell map
    void Step();
    // Method to find all the neighbors of a cell
    std::vector<Cell*> get_neighbors(int index);

    static const int NUM_CELLS = 200;

private:
    std::vector<Cell *> cells_;
};

#endif // CELLMAP_H
