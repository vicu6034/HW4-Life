#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Cell.h"

std::vector<bool> Cell::reproduce_ = {false, false, false, false, false, false, false, false};

/*
 * Have a cell become alive for left click, and dead for right click
 * @param event mouse click that is caught
*/
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !is_alive_) {
        //for left click cell becomes alive
        is_alive_ = true;
        update();
    } else if (event->button() == Qt::RightButton && is_alive_) {
        //for right click cell becomes dead
        is_alive_ = false;
        update();
    }
}

/*
 * Set cell alive status
 * @param event mouse click that is caught
*/
void Cell::SetAlive(bool alive) {
    // call update so the color changes with the alive change
    is_alive_ = alive;
    update();
}

// Set cell position
QRectF Cell::boundingRect() const {
    std::pair<int, int> pos = get_position();
    return QRectF(pos.first, pos.second, WIDTH, WIDTH);
}

// Set cell shape
QPainterPath Cell::shape() const {
    QPainterPath path;
    std::pair<int, int> pos = get_position();
    path.addRect(pos.first, pos.second, WIDTH, WIDTH);
    return path;
}

// Set cell visibility traits (color, size)
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();

    if (is_alive_) {
        painter->setBrush(QBrush(QColor(255,0,0)));
    } else {
        painter->setBrush(QBrush(QColor("transparent")));
    }

    std::pair<int, int> pos = get_position();
    painter->drawRect(QRect(pos.first, pos.second, WIDTH, WIDTH));
    painter->setBrush(b);
}

// Get the state the cell should be in for the next step
bool Cell::nextIteration() const {
    // get num of live neighbors
    int liveNeighbors = 0;
    for (Cell *c : neighbors_) {
        if (c->is_alive()) liveNeighbors++;
    }

    // handle logic based on if (this) is alive or dead
    if (is_alive_) {
        // Whether or not to stay alive
        return liveNeighbors == 2 || liveNeighbors == 3;
    } else {
        for (int i = 0; i < 8; i++) {
            if (Cell::reproduce_[i] && liveNeighbors == i) {
                return true;
            }
        }
        return false;
        // case of reproduction
//        return liveNeighbors == 3;
    }
//    return true;
}

void Cell::SetReproduce(int index, bool active) {
    Cell::reproduce_[index] = active;
}
