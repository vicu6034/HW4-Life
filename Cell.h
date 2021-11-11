#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    // paramterized constructor (index, alive)
    Cell(int index, bool alive);

    // getters index, alive, position
    int get_index() const { return index_; }
    bool is_alive() const { return is_alive_; }
    std::pair<int, int> get_position() const {
        return std::pair<int, int> { (index_ % 20) * 20 + 25, (index_ / 20) * 20 + 25 };
    }

    // setters neighbors, alive
    void SetNeighbors(std::vector<Cell*> neighbors) { neighbors_ = neighbors; }
    void SetAlive(bool alive);

    // method to determine what state the cell should be in next
    bool nextIteration() const;

    // Qt bounding and drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    // handles what happens when the mouse is clicked
    // revive cell for left click, kill cell for right click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int index_;
    bool is_alive_;

    std::vector<Cell*> neighbors_;

    static const int WIDTH = 20;
};

#endif // CELL_H
