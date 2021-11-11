#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDebug>
#include <QTimer>

#include "Cell.h"
#include "CellMap.h"

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

    // Define border variables
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

    // Add some cells for testing
    Cell *cells[200];
    for (int i = 0; i < 200; i++) {
        Cell *c = new Cell(i, arc4random() % 2);
        cells[i] = c;
        scene->addItem(c);
    }

    // Initialize CellMap
    cell_map_ = new CellMap();

    // Initialize timer
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer_->start(1000);
}

void MainWindow::TimerSlot() {
    qDebug() << "update...";
    cell_map_->Step();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_stepButton_clicked() {

}


void MainWindow::on_playButton_clicked() {

}


void MainWindow::on_pauseButton_clicked() {

}


void MainWindow::on_speedSlider_valueChanged(int value) {

}
