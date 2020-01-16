#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <cstring>
#include <QDebug>
#include <QSerialPortInfo>

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
    void textChanged(void);
    void UARTSignalRecieved(void);

    void on_actionP_riph_rique_triggered();

private:
    void write(char c);
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QString text;
};
#endif // MAINWINDOW_H
