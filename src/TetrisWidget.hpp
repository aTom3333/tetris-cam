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

public slots :
	void newGame();
    void rotate();
    void goLeft();
    void goRight();
    void fall();
//    updateGrille : demande grille uniquement si modif, fct avec tt type de grille coter crtl

private:
//Dessine les cube de la grille logique sans leur faces mitoyennes
    void drawCubes() const; 
//applique la couleur automatiquement suivant l'Id des blocks
    void setColor(const unsigned int& id) const;
//dessine le tetrominos courrant
    void drawTetromino(const unsigned int& offsetY = 0)const;
//dessine le score
    void drawScore(QPaintDevice* device) const;
    

private:
    // Timer du jeu
    QTimer timer;
	
//Le controller du jeu
    QTimer input_delay;
    bool canMove = true;
    
    int delay = 200;
    
//La grille logique
    Tetris::Tetris game;
//le rayons des cubes a dessiner
    float radius =0.5;
//des parametre permettant la rotation 3axes du dessin
    float dist =  20;
    float teta = 111;
    float phi = 96;
};


#endif // TETRISWIDGET_HPP
