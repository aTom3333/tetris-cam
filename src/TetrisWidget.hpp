#ifndef TETRISWIDGET_HPP
#define TETRISWIDGET_HPP

#include <QOpenGLWidget>
#include <QTimer>


class TetrisWidget : public QOpenGLWidget
{
    Q_OBJECT
    
public:
    explicit TetrisWidget(QWidget* parent = nullptr);
    
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int x, int y) override;

private:
    double angle;
    QTimer timer;
};


#endif // TETRISWIDGET_HPP