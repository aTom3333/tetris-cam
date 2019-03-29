#ifndef TETRISWIDGET_HPP
#define TETRISWIDGET_HPP

#include <QOpenGLWidget>
#include <QTimer>
#include "Tetromino.hpp"
#include "Grid.hpp"


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

    void keyPressEvent(QKeyEvent* event) override;
    void drawCubes() const; //dessinne les cubes sans les faces mitoyennes
    void setColor(const unsigned int& id) const;
    void drawTetromino()const;

//slots :
//    updateGrille : demande grille uniquement si modif, fct avec tt type de grille coter crtl

private:
    Tetris::Grid grid;
    Tetris::Tetromino* t = new Tetris::T_Tetromino;
    //grille de visu (origin des cubes), update via slots lors d'un signal du crtl, utile pour dessiner que face visible
    //tetriminos courrant demander a chaque paint
    float radius =0.5;
    float dist =  20;
    float teta = 150;
    float phi = 100;
};


#endif // TETRISWIDGET_HPP
