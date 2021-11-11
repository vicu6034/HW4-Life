#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Cell.h"

Cell::Cell(int index, bool alive) : index_(index), is_alive_(alive) {

}

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
