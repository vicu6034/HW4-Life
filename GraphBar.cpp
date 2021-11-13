#include "GraphBar.h"

#include <iostream>
#include <QBrush>
#include <QPainter>

/**
 * Constructor
 * @param height
 */
GraphBar::GraphBar(int height) : height_(height) {}

/*
 * Returns the position of the graph bar, adjusting for graph margins and setting
 * the x coordinate based off the index field
 */
std::pair<int, int> GraphBar::get_position() const {
    return std::pair<int, int> {(index_ * 20) + 25, (100 - height_) + 250};
}

/*
 * Sets the index of the bar and updates its x location
 * @param index
 */
void GraphBar::SetIndex(int index) {
    index_ = index;
    update();
}

// Set boundaries
QRectF GraphBar::boundingRect() const {
    std::pair<int, int> pos = get_position();
    return QRectF(pos.first, pos.second, WIDTH, height_);
}

// Set shape
QPainterPath GraphBar::shape() const {
    QPainterPath path;
    std::pair<int, int> pos = get_position();
    path.addRect(pos.first, pos.second, WIDTH, height_);
    return path;
}

// Set styling
void GraphBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(QColor(255,0,0)));

    std::pair<int, int> pos = get_position();
    painter->drawRect(QRect(pos.first, pos.second, WIDTH, height_));
    painter->setBrush(b);
}
