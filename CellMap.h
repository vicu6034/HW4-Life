#ifndef CELLMAP_H
#define CELLMAP_H

#include <vector>

#include "Cell.h"

class CellMap {
public:
    CellMap();

    void UpdateMap(CellMap *newMap);

    Position * GetNextStep(Position *pos);

    void SetCellValue(Position *pos);

    Cell * get_cell_at_pos(Position pos) { return map_[pos.x][pos.y]; }

    static double get_percent_alive();

private:
    Cell *map_[20][20];
};

#endif // CELLMAP_H
