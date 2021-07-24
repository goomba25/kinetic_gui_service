#include <QScrollBar>
#include <QDebug>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "fm_subscriber/MsgAuroraStatus.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!m_Robot.RobotInit()){
        LogAppend("Robot Init failed....");
    }
    connect(&m_Robot, &QRobot::AuroraStatusSignal, this, &MainWindow::AuroraStatusSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AuroraStatusSlot(){
    ui->lineEditDriveMode->setText(QString::fromStdString(m_Robot.m_AuroraStatus.drive_mode));
    ui->lineEditDriveStatus->setText(QString::number(m_Robot.m_AuroraStatus.drive_status));
    ui->lineEditSprayStatus->setText(QString::number(m_Robot.m_AuroraStatus.spray_status));
    ui->lineEditErrorStatus->setText(QString::number(m_Robot.m_AuroraStatus.error_status));
    LogAppend("Aurora Status received");
}

void MainWindow::LogAppend(QString log){
    QString s = log.remove('\n');
    QString ss = s.remove('\r');
    ui->textEdit->append(ss);
    ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
}

void MainWindow::on_pushButtonQuit_clicked()
{
    QApplication::quit();
}
