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
    //void drawCubes(); dessinne les cubes sans les faces mitoyennes
    //bool contain(int x, int y); verifie si la grille contient un cube a cet emplacement

//slots :
//    updateGrille : demande grille uniquement si modif, fct avec tt type de grille coter crtl

private:
    double angle;
    QTimer timer;
    //grille de visu (origin des cubes), update via slots lors d'un signal du crtl, utile pour dessiner que face visible
    //tetriminos courrant demander a chaque paint
    //radius : rayon du cube 0.5
};


#endif // TETRISWIDGET_HPP
