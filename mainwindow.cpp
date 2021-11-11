#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QString>

#include "Cell.h"
#include "CellMap.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow
) {
    // Setup UI and Scene
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

    // Initialize CellMap
    cell_map_ = new CellMap();

    for (int i = 0; i < CellMap::NUM_CELLS; i++) {
        scene->addItem(cell_map_->get_cell(i));
    }

    // Initialize timer
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    timer_speed_ = 0;

    ui->speedLabel->setText("Speed: 0");
}

void MainWindow::TimerSlot() {
    cell_map_->Step();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_stepButton_clicked() {
    cell_map_->Step();
}


void MainWindow::on_playButton_clicked() {
    timer_->start(timer_speed_);
}


void MainWindow::on_pauseButton_clicked() {
    timer_->stop();
}


void MainWindow::on_speedSlider_valueChanged(int value) {
    timer_speed_ = value;
    std::string s = "Speed: " + std::to_string(timer_speed_);
    QString q(const_cast<char*>(s.c_str()));
    ui->speedLabel->setText(q);
}
