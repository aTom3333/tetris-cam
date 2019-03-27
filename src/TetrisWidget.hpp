#ifndef TETRISWIDGET_HPP
#define TETRISWIDGET_HPP

#include <QOpenGLWidget>
#include <QTimer>
#include "Tetromino.hpp"
#include "Tetris/Grid.hpp"


class TetrisWidget : public QOpenGLWidget
{
    Q_OBJECT
    
public:
    explicit TetrisWidget(QWidget* parent = nullptr);
    
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int x, int y) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    double angle;
    QTimer timer;
    Tetris::Grid grid;
    Tetris::Tetromino* t = nullptr;
    int temp = 0;
};


#endif // TETRISWIDGET_HPP