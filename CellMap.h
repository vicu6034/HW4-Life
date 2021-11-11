#ifndef CELLMAP_H
#define CELLMAP_H

class Cell;

class CellMap {
public:
    CellMap(Cell *cells[]);

    void UpdateMap(CellMap *newMap);

    void NextStep();

    Cell * get_cell(int index) { return cells_[index]; }

    static double get_percent_alive();

    static const int NUM_CELLS = 200;

private:
    Cell *cells_[NUM_CELLS];
};

#endif // CELLMAP_H
