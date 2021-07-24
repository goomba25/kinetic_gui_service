#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

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
    void on_pushButton_clicked();

private slots:
    void on_pushButtonPublish_clicked();

private:
    void LogAppend(QString log);
    Ui::MainWindow *ui;
    QRobot m_Robot;
};

#endif // MAINWINDOW_HPP
