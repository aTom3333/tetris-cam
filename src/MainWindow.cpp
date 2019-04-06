#include "MainWindow.hpp"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget* parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
    connect(ui->actionclose,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionnew,SIGNAL(triggered()), ui->QOpenGLWidget,SLOT(newGame()));
}

void MainWindow::close()
{
    this->close();
}
