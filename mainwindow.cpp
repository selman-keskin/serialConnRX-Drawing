#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtSerialPort>



QPoint point;
QPoint previousPoint;

QByteArray data;

int coordx = 0;
int coordy = 0;



void MainWindow::putData()
{
    QString data = serial->readAll();

    QStringList coords = data.split(",");

    if (coords.size() < 2)
    {
        coordx = 0;
        coordy = 0;
    }
    else
    {
        coordx = coords[0].toInt();
        coordy = coords[1].toInt();
    }

    qDebug() << coordx << coordy;

    double rad = 5;

    scene->addEllipse(coordx-rad,
                      coordy-rad,
                      rad*2,
                      rad*2,
                QPen(Qt::NoPen), QBrush(Qt::blue));

}

void MainWindow::openSerialPort()
{



    connect(serial, SIGNAL(readyRead()), this, SLOT(putData()));

    //COM9 ---> COM11
    serial->setPortName("COM11");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    //serial->open(QIODevice::WriteOnly);
    serial->open(QIODevice::ReadWrite);

    if(!serial->open(QIODevice::ReadOnly))
    {
        qDebug() << (tr("error %1").arg(serial->error()));
        return;
    }


    //serial->waitForBytesWritten(70);
    //serial->waitForReadyRead(70);
    //serial->close();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new paintScene();           // Init graphics scene
    ui->graphicsView->setScene(scene);  // Set graphics scene

    serial = new QSerialPort();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    openSerialPort();
    ui->pushButton->setEnabled(false);
}

void MainWindow::on_closeButton_clicked()
{
    close();
}
