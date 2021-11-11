#include <iostream>

#include "CellMap.h"
#include "Cell.h"

bool chooseAlive() {
    int rando = rand() % 2;
    return (rando == 0);
}

// NEEDS TO BE FINISHED
std::vector<Cell*> CellMap::get_neighbors(int index) {
    std::vector<Cell*> neighbors;

    /* if we need to use special cases, hoping you got the math tricks
    if (index == 0) {

    } else if (index < 20) {

    } ...
    */

    //neighbors to right and left
    neighbors.push_back(get_cell(index+1));
    neighbors.push_back(get_cell(index-1));

    return neighbors;
}

CellMap::CellMap() {
    // create cells with 50% chance of being alive
    for (int i = 0; i < NUM_CELLS; i++) {
        cells_[i] = new Cell(i, chooseAlive());
    }
    // assign neighbors after all cells created
    for (int i = 0; i < NUM_CELLS; i++) {
        cells_[i]->SetNeighbors(get_neighbors(i));
    }
}

void CellMap::Step() {
    // create temp array
    Cell * temp[NUM_CELLS];
    // fill temp with new pointers
    for (int i = 0; i < NUM_CELLS; i ++) {
        temp[i] = new Cell(i, cells_[i]->nextIteration());
    }
    // set cells_ to temp
    for (int i = 0; i < NUM_CELLS; i ++) {
        cells_[i] = temp[i];
    }
    // reset neighbors
    for (int i = 0; i < NUM_CELLS; i++) {
        cells_[i]->SetNeighbors(get_neighbors(i));
    }
    // seperate for loops ebcause we need to do each step seperately to not mess up pointers
}

double CellMap::get_percent_alive() {
    int num_alive = 0;
    for (int i = 0; i < NUM_CELLS; i++) {
        if (cells_[i]->is_alive()) num_alive++;
    }
    return float(num_alive/NUM_CELLS);
}
