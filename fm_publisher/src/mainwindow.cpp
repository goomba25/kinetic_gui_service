#include <QScrollBar>
#include <QDebug>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "fm_publisher/MsgAuroraStatus.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!m_Robot.RobotInit()){
        LogAppend("Robot Init failed....");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonPublish_clicked()
{
    std::string drive_mode = ui->lineEditDriveMode->text().toStdString();
    int drive_status = ui->lineEditDriveStatus->text().toInt();
    int spray_status = ui->lineEditSprayStatus->text().toInt();
    int error_status = ui->lineEditErrorStatus->text().toInt();
    if(m_Robot.ChangeAuroraStatus(drive_mode, drive_status, spray_status, error_status)) LogAppend("Change Aurora status OK");
    else LogAppend("Change Aurora status Failed");
}

void MainWindow::LogAppend(QString log){
    QString s = log.remove('\n');
    QString ss = s.remove('\r');
    ui->textEdit->append(ss);
    ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}
