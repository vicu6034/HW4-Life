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
    // Start paused with timer at 0
    timer_speed_ = 0;
    ui->speedLabel->setText("Speed: 0");

    // Add bar for initial map
    GraphBar *b = new GraphBar(cell_map_->get_num_alive() / 2);
    b->SetIndex(0);
    scene->addItem(b);
    graph_bars_.push_back(b);

    // Initialize turnLabel to start at 1
    current_turn_ = 1;
    std::string turn_str = "Turn: " + std::to_string(current_turn_);
    QString turn_q(const_cast<char*>(turn_str.c_str()));
    ui->turnLabel->setText(turn_q);

    // Update populationLabel to show initial population
    int num_alive = cell_map_->get_num_alive();
    std::string pop_str = "Population: " + std::to_string(num_alive) + " (" + std::to_string(num_alive/2) + "%)";
    QString pop_q(const_cast<char*>(pop_str.c_str()));
    ui->popLabel->setText(pop_q);
}

void MainWindow::PerformStep() {
    // have cell map step to next turn
    cell_map_->Step();

    // add a new graph bar representing current step
    GraphBar *b = new GraphBar(cell_map_->get_num_alive() / 2);
    graph_bars_.insert(graph_bars_.begin(), b);
    scene->addItem(b);
    for (unsigned int i = 0; i < graph_bars_.size(); i++) {
        GraphBar *currentBar = graph_bars_[i];
        scene->removeItem(currentBar);
        // add item to scene only when theres < 20 so
        // they all fit on screen & we have no extra bars
        if (i < 20) {
            currentBar->SetIndex(i);
            scene->addItem(currentBar);
        } else {
            graph_bars_.pop_back();
            break;
        }
    }

    // set turnLabel with new turn count
    current_turn_++;
    std::string turn_str = "Turn: " + std::to_string(current_turn_);
    QString turn_q(const_cast<char*>(turn_str.c_str()));
    ui->turnLabel->setText(turn_q);

    // update populaton label with new population
    int num_alive = cell_map_->get_num_alive();
    std::string pop_str = "Population: " + std::to_string(num_alive) + " (" + std::to_string(num_alive/2) + "%)";
    QString pop_q(const_cast<char*>(pop_str.c_str()));
    ui->popLabel->setText(pop_q);
}


// Perform a step on every timeout of the timer
void MainWindow::TimerSlot() {
    PerformStep();
}

// Perform a step on every stepButton clicked
void MainWindow::on_stepButton_clicked() {
    PerformStep();
}

// Start the timer when the play button is clicked
void MainWindow::on_playButton_clicked() { 
    if (timer_speed_ == 0) {
        // if speed was 0, set speed to half
        timer_speed_ = 750;
        // set value on slider
        ui->speedSlider->setValue(50);
        // start timer
        timer_->start(timer_speed_);
    } else {
        // if speed was not 0 (when theres a pause)
        // then play with the last speed we were using
        timer_->start(timer_speed_);
        ui->speedSlider->setValue((1500-timer_speed_)/15);
    }
    // set label for current speed
    std::string s = "Speed: " + std::to_string((1500-timer_speed_)/15);
    QString q(const_cast<char*>(s.c_str()));
    ui->speedLabel->setText(q);
}

// Stop the timer when the pause button is clicked
void MainWindow::on_pauseButton_clicked() {
    // stop timer
    timer_->stop();
    // set speed label & slider to 0
    ui->speedSlider->setValue(0);
    std::string s = "Speed: " + std::to_string(0);
    QString q(const_cast<char*>(s.c_str()));
    ui->speedLabel->setText(q);
}

// Change timer speed to scale with the speedSlider changes
void MainWindow::on_speedSlider_valueChanged(int value) {
    if (value == 0) {
        // make sure timer is stopped when slider is at 0
        timer_->stop();
    } else {
        // convert value to timer speed & start timer
        timer_speed_ = 1500 - (value * 15);
        timer_->start(timer_speed_);
    }
    // set label for the current timer speed
    std::string s = "Speed: " + std::to_string(value);
    QString q(const_cast<char*>(s.c_str()));
    ui->speedLabel->setText(q);
}

// destructor
MainWindow::~MainWindow() {
    delete ui;
}
