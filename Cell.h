#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

struct Position {
    int x, y;
    Position(int nx, int ny) : x(nx), y(ny) {};
};

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Cell(int x, int y, bool active);

    bool is_alive() { return is_alive_; }

    Position * get_position() { return pos_; }

    void SetAlive(bool alive) { is_alive_ = alive; }

private:
    Position *pos_;
    bool is_alive_;
    static const int WIDTH;
    static const int HEIGHT;
};

#endif // CELL_H
