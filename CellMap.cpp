#include <iostream>

#include "CellMap.h"
#include "Cell.h"

// Default constructor for CellMap
CellMap::CellMap() {
    // create cells with 50% chance of being alive
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        cells_.push_back(new Cell(i, arc4random() % 2));
    }
    // assign neighbors after all cells created
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        cells_[i]->SetNeighbors(get_neighbors(i));
    }
}

// Determine all the neighbors to a cell
// Return by vector of pointers
std::vector<Cell*> CellMap::get_neighbors(int index) {
    // 10 rows x 20 columns (200 cells)
    // Calculate neighbor indices
    //      a b c
    //      d   f
    //      g h i

    int d = index - 1;
    if (d % 20 == 19 || d < 0) { d += 20; }

    int f = index + 1;
    if (f % 20 == 0) { f -= 20; }

    int a = (d + 180) % 200;
    int b = (index + 180) % 200;
    int c = (f + 180) % 200;
    int g = (d + 20) % 200;
    int h = (index + 20) % 200;
    int i = (f + 20) % 200;

    return std::vector<Cell *> {
        cells_[a],
        cells_[b],
        cells_[c],
        cells_[d],
        cells_[f],
        cells_[g],
        cells_[h],
        cells_[i]
    };
}

// Determine the next state for the entire map
void CellMap::Step() {
    std::vector<bool> next_values;
    for (Cell *c : cells_) {
        next_values.push_back(c->nextIteration());
    }
    for (int i = 0; i < NUM_CELLS; i++) {
        cells_[i]->SetAlive(next_values[i]);
    }
}

// Return what percent of cells are currently alive
int CellMap::get_num_alive() {
    int num_alive = 0;
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        if (cells_[i]->is_alive()) num_alive++;
    }
    return num_alive;
}
