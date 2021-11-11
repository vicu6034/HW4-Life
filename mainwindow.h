#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

class CellMap;
class Cell;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stepButton_clicked();

    void on_playButton_clicked();

    void on_pauseButton_clicked();

    void on_speedSlider_valueChanged(int value);

    void TimerSlot();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    CellMap *cell_map_;
    double game_speed_;
    bool paused_;

    QTimer *timer_;
    int timer_speed_;
};
#endif // MAINWINDOW_H
