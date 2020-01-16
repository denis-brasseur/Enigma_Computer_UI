#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << QSerialPortInfo::availablePorts()[0].portName();
    this->serialPort = new QSerialPort(QSerialPortInfo::availablePorts()[0].portName());
    //this->serialPort->open(QIODevice::ReadWrite);
    //qDebug() << this->serialPort->isOpen();
    this->ui->readingZone->setReadOnly(true);
    this->text = "";
    //QObject::connect(this->ui->writingZone,&QTextEdit::textChanged,this,&MainWindow::textChanged);
    connect(this->ui->writingZone,SIGNAL(textChanged()),this,SLOT(textChanged()));
    connect(this->serialPort,&QIODevice::readyRead,this,&MainWindow::UARTSignalRecieved);
}

MainWindow::~MainWindow()
{
    this->serialPort->close();
    delete this->serialPort;
    delete ui;
}

void MainWindow::write(char c){
    char buf[2] = "";
    sprintf(buf,"%c",c);
    this->serialPort->write(buf);
}

void MainWindow::textChanged(){
    this->text += this->ui->writingZone->toPlainText().back();
    qDebug() << this->ui->writingZone->toPlainText().back();
    char c = this->text.toUpper().back().toLatin1();
    if( c>='A' && c<= 'Z'){
        this->serialPort->putChar(c);
        this->serialPort->flush();
    }
    else this->ui->readingZone->setPlainText(this->text);
}
void MainWindow::UARTSignalRecieved(void){

    char c;
    this->serialPort->getChar(&c);
    if(c < 'A' || c > 'Z'){
        this->serialPort->getChar(&c);
        qDebug() << "là";
    }
    qDebug() << c;
    this->text[this->text.size()-1] = c;
    this->ui->readingZone->setPlainText(this->text);


}

void MainWindow::on_actionP_riph_rique_triggered()
{
    this->serialPort->open(QIODevice::ReadWrite);
    this->serialPort->clear();
    qDebug() << this->serialPort->isOpen();


}
