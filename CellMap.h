/*
 * CellMap Header
 * Implements a vector of Cells to be displayed by MainWindow
 * CSCI 3010 Homework 4
 * By: Vincent Curran & Philip Knott
*/

#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

class Cell;
class GraphBar;

class CellMap {
public:
    // default constructor
    CellMap();

    // get a cell by index
    Cell * get_cell(int index) { return cells_[index]; }
    // get percent of alive cells
    int get_num_alive();

    // method to determine the next cell map
    void Step();

    // method to find all the neighbors of a cell
    std::vector<Cell*> get_neighbors(int index);

    static const int NUM_CELLS = 200;

private:
    // vector of cells
    std::vector<Cell *> cells_;

}; // class CellMap

#endif // CELLMAP_H
