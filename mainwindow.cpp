#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QString>

#include "Cell.h"
#include "CellMap.h"
#include "GraphBar.h"

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

    GraphBar *b = new GraphBar(cell_map_->get_num_alive() / 2);
    b->SetIndex(0);
    scene->addItem(b);
    graph_bars_.push_back(b);

    timer_speed_ = 0;
    ui->speedLabel->setText("Speed: 0");

    current_turn_ = 1;
    std::string turn_str = "Turn: " + std::to_string(current_turn_);
    QString turn_q(const_cast<char*>(turn_str.c_str()));
    ui->turnLabel->setText(turn_q);

    int num_alive = cell_map_->get_num_alive();
    std::string pop_str = "Population: " + std::to_string(num_alive) + " (" + std::to_string(num_alive/2) + "%)";
    QString pop_q(const_cast<char*>(pop_str.c_str()));
    ui->popLabel->setText(pop_q);
}

void MainWindow::TimerSlot() {
    cell_map_->Step();

    GraphBar *b = new GraphBar(cell_map_->get_num_alive() / 2);
    graph_bars_.insert(graph_bars_.begin(), b);
    scene->addItem(b);
    for (unsigned int i = 0; i < graph_bars_.size(); i++) {
        GraphBar *currentBar = graph_bars_[i];
        scene->removeItem(currentBar);
        if (i < 20) {
            currentBar->SetIndex(i);
            scene->addItem(currentBar);
        } else {
            graph_bars_.pop_back();
            break;
        }
    }

    current_turn_++;
    std::string turn_str = "Turn: " + std::to_string(current_turn_);
    QString turn_q(const_cast<char*>(turn_str.c_str()));
    ui->turnLabel->setText(turn_q);

    int num_alive = cell_map_->get_num_alive();
    std::string pop_str = "Population: " + std::to_string(num_alive) + " (" + std::to_string(num_alive/2) + "%)";
    QString pop_q(const_cast<char*>(pop_str.c_str()));
    ui->popLabel->setText(pop_q);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_stepButton_clicked() {
    cell_map_->Step();

    GraphBar *b = new GraphBar(cell_map_->get_num_alive() / 2);
    graph_bars_.insert(graph_bars_.begin(), b);
    scene->addItem(b);
    for (unsigned int i = 0; i < graph_bars_.size(); i++) {
        GraphBar *currentBar = graph_bars_[i];
        scene->removeItem(currentBar);
        if (i < 20) {
            currentBar->SetIndex(i);
            scene->addItem(currentBar);
        } else {
            graph_bars_.pop_back();
            break;
        }
    }

    current_turn_++;
    std::string s = "Turn: " + std::to_string(current_turn_);
    QString q(const_cast<char*>(s.c_str()));
    ui->turnLabel->setText(q);

    int num_alive = cell_map_->get_num_alive();
    std::string pop_str = "Population: " + std::to_string(num_alive) + " (" + std::to_string(num_alive/2) + "%)";
    QString pop_q(const_cast<char*>(pop_str.c_str()));
    ui->popLabel->setText(pop_q);
}


void MainWindow::on_playButton_clicked() {
    if (timer_speed_ == 0) {
        timer_->start(750);
        ui->speedSlider->setValue(50);
        std::string s = "Speed: " + std::to_string(50);
        QString q(const_cast<char*>(s.c_str()));
        ui->speedLabel->setText(q);
    } else {
        timer_->start(timer_speed_);
    }
}


void MainWindow::on_pauseButton_clicked() {
    timer_->stop();
}


void MainWindow::on_speedSlider_valueChanged(int value) {
    if (value == 0) {
        timer_->stop();
    } else {
        timer_speed_ = 1500 - (value * 15);
        timer_->start(timer_speed_);
    }
    std::string s = "Speed: " + std::to_string(value);
    QString q(const_cast<char*>(s.c_str()));
    ui->speedLabel->setText(q);
}
