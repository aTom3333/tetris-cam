#include "TetrisWidget.hpp"
#include <GL/glu.h>
#include <QKeyEvent>
#include <QDebug>


TetrisWidget::TetrisWidget(QWidget* parent) :
    QOpenGLWidget{parent}, grid{10, 20}
{
    setFocusPolicy(Qt::StrongFocus);

    connect(&timer, &QTimer::timeout, [this]
    {
        angle += 1.0 / 4.0;
        update();
    });

    timer.setInterval(10);
    timer.start();

    grid(0, 0) = 1;
    grid(9, 0) = 1;
    grid(0, 19) = 1;
    grid(9, 19) = 1;
    
    grid(2, 5) = 1;
    grid(3, 14) = 1;
}

void TetrisWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(5, 10, 20, 5, 10, 0, 0, 1, 0);

    //glRotated(angle, 0, 1, 0);

    glBegin(GL_QUADS);
    glColor3ub(100, 100, 100);

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 20; j++)
        {
            if(grid(i, j))
            {
                glVertex3f(i + 0.5, j + 0.5, 0);
                glVertex3f(i - 0.5, j + 0.5, 0);
                glVertex3f(i - 0.5, j - 0.5, 0);
                glVertex3f(i + 0.5, j - 0.5, 0);
            }

        }
    glColor3ub(255, 0, 0);

    for(int i = 0; i < 4; i++)
    {
        auto c = t->getOrigin() + t->getBlocks()[i];

        glVertex3f(c.x + 0.5, c.y + 0.5, 0);
        glVertex3f(c.x - 0.5, c.y + 0.5, 0);
        glVertex3f(c.x - 0.5, c.y - 0.5, 0);
        glVertex3f(c.x + 0.5, c.y - 0.5, 0);
    }
    /*
    
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(1,-1,0);

    glColor3ub(255,255,0);
    glVertex3f(1,1,0);
    glVertex3f(1,-1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(-1,1,0);

    glColor3ub(255,0,255);
    glVertex3f(1,-1,0);
    glVertex3f(1,-1,0);
    glVertex3f(-1,-1,0);
    glVertex3f(-1,-1,0);

    glColor3ub(0,255,0);
    glVertex3f(1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(-1,1,0);
    glVertex3f(1,1,0);
/*
    glColor3ub(0,255,255);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,1,1);

    glColor3ub(0,0,255);
    glVertex3f(1,1,-1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);*/
    glEnd();
}

void TetrisWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();

    glClearColor(0.8, 0.8, 0.8, 1);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) width() / height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void TetrisWidget::resizeGL(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) width() / height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void TetrisWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_A:
            t->rotateCCW(grid);
            update();
            break;

        case Qt::Key_P:
            t->rotateCW(grid);
            update();
            break;

        case Qt::Key_Up:
            t->translate(grid, 0, 1);
            update();
            break;

        case Qt::Key_Down:
            t->translate(grid, 0, -1);
            update();
            break;

        case Qt::Key_Left:
            t->translate(grid, -1, 0);
            update();
            break;

        case Qt::Key_Right:
            t->translate(grid, 1, 0);
            update();
            break;
    }
}
