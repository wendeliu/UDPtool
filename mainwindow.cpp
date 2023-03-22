#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPushButton"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(this->ui->pushButton,&QPushButton::clicked,this,&MainWindow::on_pushButton_clicked);
    connect(&sock,SIGNAL(readyRead()),this,SLOT(udpReceive()));
    //sock.bind(19191);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::udpReceive()
{
    QHostAddress sender;
       u_int16_t port;
       int i=0;
       while (sock.hasPendingDatagrams())
       {
            QByteArray datagram;
            QString data;
            QStringList cmdList;
            i+=1;
            datagram.resize(sock.pendingDatagramSize());
            sock.readDatagram(datagram.data(),datagram.size(),&sender,&port);
            data=QString(datagram);
            //this->ui->plainTextEdit_4->setPlainText(data);
            //this->ui->pushButton->setText(QString().setNum(i));
            cmdList=data.split(',');


            int cnt=cmdList[cmdList.count()-1].toInt();


            this->ui->tableWidget->clear();
            this->ui->tableWidget->setRowCount(2);
            this->ui->tableWidget->setColumnCount(cnt);

            for(int j=1;j<cnt+1;j++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(cmdList[j*2-1]);
                this->ui->tableWidget->setItem(0, j-1, newItem);
                newItem = new QTableWidgetItem(cmdList[j*2]);
                this->ui->tableWidget->setItem(1, j-1, newItem);
            }

       }
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


void MainWindow::on_start_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="SYSMODE,3";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt();
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}


void MainWindow::on_stop_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="SYSMODE,5";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt();
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}


void MainWindow::on_log_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="UDP_LOG_START";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt()+1;
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}


void MainWindow::on_stop_log_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="UDP_LOG_STOP";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt()+1;
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}


void MainWindow::on_pushButton_2_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="KEY,LEFT_KEY,1,KEYEND";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt()+2;
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}


void MainWindow::on_pushButton_3_clicked()
{
    QHostAddress ip;
    ip=QHostAddress(this->ui->plainTextEdit->toPlainText());
    QString cmd="KEY,RIGHT_KEY,1,KEYEND";
    int len=cmd.length();
    int port=this->ui->plainTextEdit_2->toPlainText().toInt()+2;
    sock.writeDatagram(cmd.toLocal8Bit().constData(),len,ip,port);
}

