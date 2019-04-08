#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow{parent},
    ui{new Ui::MainWindow}
{
    ui->setupUi(this);
	
    connect(ui->actionclose,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionnew,SIGNAL(triggered()), ui->QOpenGLWidget,SLOT(newGame()));
    connect(ui->graphicsView->getHand(), SIGNAL(rotate()), ui->QOpenGLWidget, SLOT(rotate()));
    connect(ui->graphicsView->getHand(), SIGNAL(strafeLeft()), ui->QOpenGLWidget, SLOT(goLeft()));
    connect(ui->graphicsView->getHand(), SIGNAL(strafeRight()), ui->QOpenGLWidget, SLOT(goRight()));
    connect(ui->graphicsView->getHand(), SIGNAL(fastFall()), ui->QOpenGLWidget, SLOT(fall()));
}

void MainWindow::close()
{
    this->close();
}


