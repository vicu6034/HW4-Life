/*
 * MainWindow Header
 * Implements QMainWindow to display the Game of Life
 * CSCI 3010 Homework 4
 * By: Vincent Curran & Philip Knott
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

class CellMap;
class Cell;
class GraphBar;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // constructor/destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void PerformStep();

private slots:
    // default slots for buttons
    void on_stepButton_clicked();
    void on_playButton_clicked();
    void on_pauseButton_clicked();

    // default slot for speed slider
    void on_speedSlider_valueChanged(int value);

    // custom slot to trigger on every timeout of timer
    void TimerSlot();

    void on_resetButton_clicked();

    void on_checkBox_0_toggled(bool checked);

    void on_checkBox_1_stateChanged(int arg1);

    void on_checkBox_0_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

    void on_checkBox_6_stateChanged(int arg1);

    void on_checkBox_7_stateChanged(int arg1);

private:
    // Qt Ui and Scene
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    // CellMap and GraphBars to display
    CellMap *cell_map_;
    std::vector<GraphBar *> graph_bars_;

    // QTimer to control speed
    QTimer *timer_;
    int timer_speed_;
    int current_turn_;

}; // class MainWindow inherits QMainWindow

#endif // MAINWINDOW_H
