#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Cell(int index, bool alive);

    int get_index() {return index_;}
    bool is_alive() { return is_alive_; }

    void SetAlive(bool alive);
    void SetNeighbors(std::vector<Cell*> neighbors) {neighbors_ = neighbors;}

    std::pair<int, int> get_position() const {
        return std::pair<int, int> { (index_ % 20) * 20 + 25, (index_ / 20) * 20 + 25 };
    }

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    bool nextIteration();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void CellSelected(Cell * c);

private:
    int index_;
    bool is_alive_;

    std::vector<Cell*> neighbors_;

    static const int WIDTH = 20;
};

#endif // CELL_H
