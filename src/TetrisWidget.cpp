#include "TetrisWidget.hpp"
#include <GL/glu.h>


TetrisWidget::TetrisWidget(QWidget* parent) :
    QOpenGLWidget{parent}
{
    connect(&timer,  &QTimer::timeout, [this] {
        angle += 1.0 / 12.0;
        update();
    });

    timer.setInterval(10);
    timer.start();
}

void TetrisWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(3, 2, 3, 0, 0, 0, 0, 1, 0);
    
    glRotated(angle, 0, 1, 0);

    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex3f(1,1,1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);

    glColor3ub(255,255,0);
    glVertex3f(1,1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);

    glColor3ub(255,0,255);
    glVertex3f(1,-1,-1);
    glVertex3f(1,-1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);

    glColor3ub(0,255,0);
    glVertex3f(1,1,-1);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,1,1);
    glVertex3f(1,1,1);

    glColor3ub(0,255,255);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);

    glColor3ub(0,0,255);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glEnd();
}

void TetrisWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();
    
    glClearColor(0.8, 0.8, 0.8, 1);
    
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)width()/height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void TetrisWidget::resizeGL(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double)width()/height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}
