#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPushButton"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
    sock.bind(19191);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QHostAddress ip;

    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd=this->ui->plainTextEdit_3->toPlainText();
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt();
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);

}

