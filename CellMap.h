#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

#include "Cell.h"

class CellMap {
public:
    CellMap();

    void UpdateMap(CellMap *newMap);

    void NextStep();

    void SetCellValue(int index);

    Cell * get_cell(int index) { return cells_[index]; }

    static double get_percent_alive();

private:
    Cell *cells_[200];
};

#endif // CELLMAP_H
