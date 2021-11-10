#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow
) {
    ui->setupUi(this);

    QGraphicsView * view = ui->plotGraphicsView;

    scene = new QGraphicsScene;
    view->setScene(scene);
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    qsrand(static_cast<unsigned>(QTime::currentTime().msec()));

    // Add grid border
//    int frameWidth = view->frameSize().width();
//    int frameHeight = view->frameSize().height();
//    int margin = 50;
//    int marginBottom = 150;
//    scene->addLine(margin, margin, frameWidth - margin, margin);
//    scene->addLine(margin, frameHeight - marginBottom, frameWidth - margin, frameHeight - marginBottom);
//    scene->addLine(margin, margin, margin, frameHeight - marginBottom);
//    scene->addLine(frameWidth - margin, margin, frameWidth - margin, frameHeight - marginBottom);

    int gridWidth = 400;
    int gridHeight = 200;
    int graphWidth = 400;
    int graphHeight = 100;
    int margin = 25;
    int graphMargin = 250;

    // Grid outline
    scene->addLine(margin, margin, margin, margin + gridHeight);
    scene->addLine(margin, margin, margin + gridWidth, margin);
    scene->addLine(margin + gridWidth, margin, margin + gridWidth, margin + gridHeight);
    scene->addLine(margin, margin + gridHeight, margin + gridWidth, margin + gridHeight);

    // Graph outline
    scene->addLine(margin, graphMargin, margin + graphWidth, graphMargin);
    scene->addLine(margin, graphMargin + graphHeight, margin + graphWidth, graphMargin + graphHeight);
    scene->addLine(margin, graphMargin, margin, graphMargin + graphHeight);
    scene->addLine(margin + graphWidth, graphMargin, margin + graphWidth, graphMargin + graphHeight);
}

MainWindow::~MainWindow() {
    delete ui;
}

