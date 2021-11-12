#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include <QGraphicsItem>

class GraphBar : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    GraphBar(int height);

    int get_height() const { return height_; }

    void SetIndex(int index);

    std::pair<int, int> get_position() const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int height_, index_;
    static const int WIDTH = 20;

};

#endif // GRAPHBAR_H
