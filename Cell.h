#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

struct Position {
    int x_, y_;
    Position(int x, int y) : x_(x), y_(y) {};
};

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Cell(int x, int y, bool active);

    bool is_alive() { return is_alive_; }

    Position * get_position() { return pos_; }

    void SetAlive(bool alive) { is_alive_ = alive; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void CellSelected(Cell * c);

private:
    Position *pos_;
    bool is_alive_;

    static const int WIDTH;
    static const int HEIGHT;
};

#endif // CELL_H
