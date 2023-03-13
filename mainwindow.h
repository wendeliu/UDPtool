#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QUdpSocket"
#include <QChart>
#include <QLineSeries>
#include <QChartView>

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
    void on_pushButton_clicked();
    void udpReceive();
    void on_start_clicked();

    void on_stop_clicked();

    void on_log_clicked();

    void on_stop_log_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket sock;
};
#endif // MAINWINDOW_H
