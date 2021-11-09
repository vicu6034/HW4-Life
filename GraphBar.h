#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include <QGraphicsItem>

class GraphBar : public QGraphicsItem {

public:
    GraphBar(int height);

    int get_height() { return height_; }

    QPainterPath shape() const override;

private:
    int height_;
    static const int WIDTH;

};

#endif // GRAPHBAR_H
