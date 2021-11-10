#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Cell(int index, bool alive);

    bool is_alive() { return is_alive_; }

    std::pair<int, int> get_position() const {
        return std::pair<int, int> { (index_ % 20) * 20 + 25, (index_ / 20) * 20 + 25 };
    }

    void SetAlive(bool alive) { is_alive_ = alive; }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void CellSelected(Cell * c);

private:
    int index_;
    bool is_alive_;

    static const int WIDTH = 20;
};

#endif // CELL_H
