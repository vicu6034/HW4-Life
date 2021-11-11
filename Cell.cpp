#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Cell.h"

Cell::Cell(int index, bool alive) : index_(index), is_alive_(alive) {}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "cell clicked!";
}

void Cell::SetAlive(bool alive) {
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
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);

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

bool Cell::nextIteration() {
    // set ret v to current status
    bool ret = is_alive_;
    // get num of live neighbors
    int liveNeighbors = 0;
    for (unsigned int i = 0; i < neighbors_.size(); i++) {
        if (neighbors_[i]->is_alive()) liveNeighbors++;
    }
    // handle logic based on if (this) is alive or dead
    if (is_alive_) {
        // cases of under and overpopulation
        if ((liveNeighbors < 2) || (liveNeighbors > 3)) ret = false;
    } else {
        // case of reproduction
        if (liveNeighbors == 3) ret = true;
    }
    return ret;
}
