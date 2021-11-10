#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "Cell.h"

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "cell clicked!";

}

// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Cell::boundingRect() const
{
    return QRectF(pos_->x_, pos_->y_, WIDTH, HEIGHT);
}

// define the actual shape of the object
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(pos_->x_, pos_->y_, WIDTH, HEIGHT);
    return path;
}

// called by Qt to actually display the point
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(QColor(0,0,0)));

    painter->drawRect(QRect(this->pos_->x_, this->pos_->y_, WIDTH, HEIGHT));
    painter->setBrush(b);
}
