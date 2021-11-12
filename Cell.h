/*
 * Cell Header
 * Implements a single Cell for the CellMap
 * Cells have a color representing wether they're alive or dead
 * CSCI 3010 Homework 4
 * By: Vincent Curran & Philip Knott
*/

#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    // paramterized constructor (index, alive)
    Cell(int index, bool alive) : index_(index), is_alive_(alive) {}

    // getters index, alive, position
    int get_index() const { return index_; }
    bool is_alive() const { return is_alive_; }
    std::pair<int, int> get_position() const {
        return std::pair<int, int>{ ((index_ % 20) * 20 + 25), ((index_ / 20) * 20 + 25) };
    }

    // setters neighbors, alive
    void SetNeighbors(std::vector<Cell*> neighbors) { neighbors_ = neighbors; }
    void SetAlive(bool alive);

    // method to determine what state the cell should be in next
    bool nextIteration() const;

    // necessary Qt bounding and drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    // handles what happens when the mouse is clicked
    // revive cell for left click, kill cell for right click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    // represents where Cell is in Map
    int index_;
    // represents if cell is alive or dead
    bool is_alive_;

    QColor color_;

    // hold vec of neighbor cells to determine nextIteration
    std::vector<Cell*> neighbors_;

    // all cells have the same width
    static const int WIDTH = 20;

}; // class cell inherits QGraphicsItem

#endif // CELL_H
