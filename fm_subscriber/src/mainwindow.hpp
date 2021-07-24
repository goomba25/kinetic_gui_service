#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "fm_subscriber/MsgAuroraStatus.h"
#include "qrobot.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonQuit_clicked();
    void AuroraStatusSlot();

private:
    void LogAppend(QString log);
    Ui::MainWindow *ui;
    QRobot m_Robot;
};

#endif // MAINWINDOW_HPP
