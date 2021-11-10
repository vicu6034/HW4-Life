#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Cell.h"

Cell::Cell(int index, bool alive) : index_(index), is_alive_(alive) {}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "cell clicked!";
}

// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Cell::boundingRect() const
{
    std::pair<int, int> pos = get_position();
    return QRectF(pos.first, pos.second, WIDTH, WIDTH);
}

// define the actual shape of the object
QPainterPath Cell::shape() const
{
    QPainterPath path;
    std::pair<int, int> pos = get_position();
    path.addRect(pos.first, pos.second, WIDTH, WIDTH);
    return path;
}

// called by Qt to actually display the point
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(QColor(0,0,0)));

    std::pair<int, int> pos = get_position();
    painter->drawRect(QRect(pos.first, pos.second, WIDTH, WIDTH));
    painter->setBrush(b);
}
