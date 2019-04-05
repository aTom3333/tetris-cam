#ifndef TETRISWIDGET_HPP
#define TETRISWIDGET_HPP

#include <QOpenGLWidget>
#include <QTimer>
#include "Tetris/Tetris.hpp"

//Class gerant l'aspet visuel du jeux
//dessinne la grille avec les blocks, le tetrominos courrant
//dessine le score
//Auteur : Axel POULAT
class TetrisWidget : public QOpenGLWidget
{
    Q_OBJECT
    
public:
//constructeur
    explicit TetrisWidget(QWidget* parent = nullptr);
    
protected:
//Methode redéfinie d'openGl
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int x, int y) override;
	void keyPressEvent(QKeyEvent* event) override;

//slots :
//    updateGrille : demande grille uniquement si modif, fct avec tt type de grille coter crtl

//Dessine les cube de la grille logique sans leur faces mitoyennes
    void drawCubes() const; 
//applique la couleur automatiquement suivant l'Id des blocks
    void setColor(const unsigned int& id) const;
//dessine le tetrominos courrant
    void drawTetromino(const unsigned int& offsetY = 0)const;
//dessine le score
    void drawScore() const;

//slots :
//    updateGrille : demande grille uniquement si modif, fct avec tt type de grille coter crtl

private:
    // Timer du jeu
    QTimer timer;
    
//La grille logique
    Tetris::Tetris game;
//le rayons des cubes a dessiner
    float radius =0.5;
//des parametre permettant la rotation 3axes du dessin
    float dist =  20;
    float teta = 150;
    float phi = 100;
};


#endif // TETRISWIDGET_HPP
