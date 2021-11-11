#include <iostream>

#include "CellMap.h"
#include "Cell.h"

// Helper to return true/false with 50% chance
// Used to determine if a specific cell should be alive or dead
bool chooseAlive() {
    int rando = arc4random() % 2;
    return (rando == 0);
}

// Default constructor for CellMap
CellMap::CellMap() {
    // create cells with 50% chance of being alive
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        cells_[i] = new Cell(i, arc4random() % 2);
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

    // Left neighbor
    int d = index - 1;
    if (d % 10 == 9) d += 20;

    // Right neighbor
    int f = index + 1;
    if (f % 10 == 0) f -= 20;

    // Top neighbors
    int a = (d + 180) % 200;
    int b = (index + 180) % 200;
    int c = (f + 180) % 200;

    // Bottom neighbors
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
    // create temp array
    Cell * temp[NUM_CELLS];
    // fill temp with new pointers
    for (unsigned int i = 0; i < NUM_CELLS; i ++) {
        temp[i] = new Cell(i, cells_[i]->nextIteration());
    }
    // set cells_ to temp
    for (unsigned int i = 0; i < NUM_CELLS; i ++) {
        cells_[i] = temp[i];
    }
    // reset neighbors
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        cells_[i]->SetNeighbors(get_neighbors(i));
    }
    // seperate for loops because we need to do each step seperately to not mess up pointers
}

// Return what percent of cells are currently alive
double CellMap::get_percent_alive() {
    int num_alive = 0;
    for (unsigned int i = 0; i < NUM_CELLS; i++) {
        if (cells_[i]->is_alive()) num_alive++;
    }
    return float(num_alive/NUM_CELLS);
}
