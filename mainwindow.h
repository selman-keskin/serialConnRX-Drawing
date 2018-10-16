#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <paintscene.h>
#include <QtSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    paintScene *scene;  // We declare a custom graphic scene
    QSerialPort *serial;

private slots:
    void putData();
    void openSerialPort();

    void on_pushButton_clicked();
    void on_closeButton_clicked();
};

#endif // MAINWINDOW_H
