#include <iostream>

#include "CellMap.h"
#include "Cell.h"

CellMap::CellMap(Cell *cells[]) {
    for (int i = 0; i < NUM_CELLS; i++) {
        cells_[i] = cells[i];
    }
}

void CellMap::UpdateMap(CellMap *newMap) {

}

void CellMap::NextStep() {

}

static double get_percent_alive() {
    return 0.0;
}
