/*
 * GraphBar Header
 * Implements bars for a bar graph
 * Which will represent % of population alive in Game of Life
 * CSCI 3010 Homework 4
 * By: Vincent Curran & Philip Knott
*/

#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include <QGraphicsItem>

class GraphBar : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    // paramterized constructor
    GraphBar(int height);

    // getters height position
    int get_height() const { return height_; }
    std::pair<int, int> get_position() const;

    // setter index
    void SetIndex(int index);

    // necessary Qt drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    // height based off number of alive cells
    // index is position in graphused to calculate position
    int height_, index_;

    // all bars have the same width
    static const int WIDTH = 20;

}; // class GraphBar inherits QGraphicsItem

#endif // GRAPHBAR_H
