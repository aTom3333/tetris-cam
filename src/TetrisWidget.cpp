#include "TetrisWidget.hpp"
#include <GL/glu.h>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>
#include <QPainter>


TetrisWidget::TetrisWidget(QWidget* parent) :
    QOpenGLWidget{parent}
{
    setFocusPolicy(Qt::StrongFocus);

    QSurfaceFormat f = format();
    f.setSamples(8);
    setFormat(f);
    glEnable(GL_MULTISAMPLE);
    
    connect(&timer, &QTimer::timeout, [this]() {
        game.goDown();
        update();
    });
    
    connect(&input_delay, &QTimer::timeout, [this]() {
        canMove = true;
    });
    
    timer.setInterval(300);
    timer.start();

}

void TetrisWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float x,y,z;
    x=dist*sin(teta*M_PI/180)*cos(phi*M_PI/180);
    y=dist*cos(teta*M_PI/180);
    z=dist*sin(teta*M_PI/180)*sin(phi*M_PI/180);
    gluLookAt(x,y,z,0,0,0,0,1,0);
    //gluLookAt(-2, -15, 10, 0, 0, 0, 0, 1, 0);
    glRotated(3,0,0,1);


    // Reglage de la lampe
    GLfloat colorAmbiant_tab[] = {0.25,0.25,0.25,1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,colorAmbiant_tab);
    GLfloat colorDiffuse_tab[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,colorDiffuse_tab);
    GLfloat colorPos_tab[] = {-1,-4,10.0,0.0};
    glLightfv(GL_LIGHT0,GL_POSITION,colorPos_tab);

    glDisable(GL_LIGHTING);
    
    //dessin de la grille
    glBegin(GL_LINES);
        glColor3ub(196,196,196);
        for(int i=10; i>=-10; i--){
            glVertex3f(-5,i,0);
            glVertex3f(5,i,0);
        }

        for(int i=-5;i<6;i++){
            glVertex3f(i,10,0);
            glVertex3f(i,-10,0);
        }
    glEnd();

    glEnable(GL_LIGHTING);

    //dessin des cube de la grille
    drawCubes();
    //dessin du tetrominos en chute
    drawTetromino();
    drawScore(this);

//    //appelle au crlt pour avoir score
//    QString scoreStr = QString::number(game.getScore());
//    QPainter painter;
//    painter.begin(this);
//    painter.setFont(QFont("Arial", 30));
//    painter.setPen(QColor::fromRgb(255,255,255));
//    painter.drawText(30,30,scoreStr);
//    painter.end();
}

void TetrisWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();

    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) width() / height(), 0.1, 100);
    glMatrixMode(GL_MODELVIEW);

    // Activation de la lumiere
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void TetrisWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, (double) width / height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void TetrisWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_A:
            game.rotateLeft();
            update();
            break;

        case Qt::Key_P:
            game.rotateRight();
            update();
            break;
            
        case Qt::Key_D:
             phi++;
            break;

        case Qt::Key_Q:
             phi--;
            break;

        case Qt::Key_Z:
            if(teta>1){
                teta--;
                }
            break;

        case Qt::Key_S:
            if(teta<179){
                teta++;
            }
            break;

        case Qt::Key_H:
            qDebug() << "teta:" << teta;
            qDebug() << "phi:" << phi;
            break;
              
        case Qt::Key_Down:
            game.goDown();
            update();
            break;

        case Qt::Key_Left:
            game.goLeft();
            update();
            break;

        case Qt::Key_Right:
            game.goRight();
            update();
            break;
    }
    update();
}

void TetrisWidget::drawCubes() const
{
    auto const& grid = game.getGrid();
    
    for(unsigned int i = 0; i < 10; i++){
        for(unsigned int j = 0; j < 20; j++){
            if(grid(i,j) != 0){
                glBegin(GL_QUADS);

                setColor(grid(i,j)); //fct qui applique la couleur
                //fct applicage de texture en fct de id

                //face avant
                glNormal3f(0, 0, 1);
                glVertex3f(i-radius-4.5, j-radius-9.5, 1);
                glVertex3f(i+radius-4.5, j-radius-9.5, 1);
                glVertex3f(i+radius-4.5, j+radius-9.5, 1);
                glVertex3f(i-radius-4.5, j+radius-9.5, 1);


                //face arriere
                glNormal3f(0, 0, -1);
                glVertex3f(i-radius-4.5, j-radius-9.5, 0);
                glVertex3f(i+radius-4.5, j-radius-9.5, 0);
                glVertex3f(i+radius-4.5, j+radius-9.5, 0);
                glVertex3f(i-radius-4.5, j+radius-9.5, 0);

                if(i==0 || grid(i-1,j) == 0){
                    //face coter gauche
                    glNormal3f(-1, 0, 0);
                    glVertex3f(i-radius-4.5, j-radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j+radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j+radius-9.5, 0);
                    glVertex3f(i-radius-4.5, j-radius-9.5, 0);
                }

                if(i==9 || grid(i+1,j) == 0){
                    //face coter droite
                    glNormal3f(1, 0, 0);
                    glVertex3f(i+radius-4.5, j-radius-9.5, 1);
                    glVertex3f(i+radius-4.5, j+radius-9.5, 1);
                    glVertex3f(i+radius-4.5, j+radius-9.5, 0);
                    glVertex3f(i+radius-4.5, j-radius-9.5, 0);
                }

                if(j==19 || grid(i,j+1) ==0){
                    //face dessus
                    glNormal3f(0, 1, 0);
                    glVertex3f(i+radius-4.5, j+radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j+radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j+radius-9.5, 0);
                    glVertex3f(i+radius-4.5, j+radius-9.5, 0);
                }

                if(j==0 || grid(i,j-1) ==0){
                    //face dessous
                    glNormal3f(0, -1, 0);
                    glVertex3f(i+radius-4.5, j-radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j-radius-9.5, 1);
                    glVertex3f(i-radius-4.5, j-radius-9.5, 0);
                    glVertex3f(i+radius-4.5, j-radius-9.5, 0);
                }
                glEnd();
            }
        }
    }
}

void TetrisWidget::setColor(const unsigned int& id) const
{
    GLfloat colorDiffuse_tab[4]; //RGBA
    colorDiffuse_tab[3] = 1;

    unsigned int colorID = id & 7;
    switch (colorID) {
        case 1://I cyan
            colorDiffuse_tab[0] = 0.188;
            colorDiffuse_tab[1] = 0.78;
            colorDiffuse_tab[2] = 0.937;
            break;
        case 2://O jaune
            colorDiffuse_tab[0] = 0.969;
            colorDiffuse_tab[1] = 0.831;
            colorDiffuse_tab[2] = 0.027;
            break;
        case 3://J bleu
            colorDiffuse_tab[0] = 0;
            colorDiffuse_tab[1] = 0;
            colorDiffuse_tab[2] = 1;
            break;
        case 4://L orange
            colorDiffuse_tab[0] = 0.937;
            colorDiffuse_tab[1] = 0.475;
            colorDiffuse_tab[2] = 0.133;
            break;
        case 5://S vert
            colorDiffuse_tab[0] = 0;
            colorDiffuse_tab[1] = 1;
            colorDiffuse_tab[2] = 0.04;
            break;
        case 6://Z rouge
            colorDiffuse_tab[0] = 1;
            colorDiffuse_tab[1] = 0.04;
            colorDiffuse_tab[2] = 0;
            break;
        case 7://T magenta
            colorDiffuse_tab[0] = 0.678;
            colorDiffuse_tab[1] = 0.306;
            colorDiffuse_tab[2] = 0.62;
            break;
        default: //autre noir
            colorDiffuse_tab[0] = 0;
            colorDiffuse_tab[1] = 0;
            colorDiffuse_tab[2] = 0;
            break;
    }
    glMaterialfv(GL_FRONT, GL_AMBIENT, colorDiffuse_tab);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorDiffuse_tab);
}

void TetrisWidget::drawTetromino(const unsigned int& offsetY) const
{
    if(!game.getTetromino())
        return;
    
    setColor(game.getTetromino()->getId() & 7);
    Tetris::Coord origin = game.getTetromino()->getOrigin();
    std::array<Tetris::Coord, 4> blocks = game.getTetromino()->getBlocks();
    bool drawing = true;

    glBegin(GL_QUADS);
    for(size_t i=0; i<blocks.size();i++){
        //face avant
        glNormal3f(0, 0, 1);
        glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
        glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
        glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);
        glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);

        //face arriere
        glNormal3f(0, 0, -1);
        glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
        glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
        glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);
        glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);

        //face coter gauche
        for(size_t j=0; j<blocks.size();j++){
            //si il existe un block plus a gauche mais au meme niveau vertical
            if((blocks[j].x+origin.x < blocks[i].x+origin.x) && (blocks[j].y+origin.y == blocks[i].y+origin.y)){
                drawing = false;
                break;
            }
        }
        if(drawing){
            glNormal3f(-1, 0, 0);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
        }
        drawing=true;

        //face coter droite
        for(size_t j=0; j<blocks.size();j++){
            //si il existe un block plus a droite mais au meme niveau vertical
            if((blocks[j].x+origin.x > blocks[i].x+origin.x) && (blocks[j].y+origin.y == blocks[i].y+origin.y)){
                drawing = false;
                break;
            }
        }
        if(drawing){
            glNormal3f(1, 0, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
        }
        drawing=true;

        //face dessus
        for(size_t j=0; j<blocks.size();j++){
            //si il existe un block plus en haut mais au meme niveau horizontal
            if((blocks[j].x+origin.x == blocks[i].x+origin.x) && (blocks[j].y+origin.y > blocks[i].y+origin.y)){
                drawing = false;
                break;
            }
        }
        if(drawing){
            glNormal3f(0, 1, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y+radius-9.5+offsetY, 0);
        }
        drawing=true;

        //face dessous
        for(size_t j=0; j<blocks.size();j++){
            //si il existe un block plus en dessous mais au meme niveau horizontal
            if((blocks[j].x+origin.x == blocks[i].x+origin.x) && (blocks[j].y+origin.y < blocks[i].y+origin.y)){
                drawing = false;
                break;
            }
        }
        if(drawing){
            glNormal3f(0, -1, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 1);
            glVertex3f(blocks[i].x+origin.x-radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
            glVertex3f(blocks[i].x+origin.x+radius-4.5, blocks[i].y+origin.y-radius-9.5+offsetY, 0);
        }
        drawing=true;
    }
    glEnd();
}

void TetrisWidget::drawScore(QPaintDevice* device) const
{
    //appelle au crlt pour avoir score
    QString scoreStr = QString::number(game.getScore());

    //enleve le z buffer pour dessiner du text en 2D
    glDisable(GL_DEPTH_TEST);
    QPainter painter;
    painter.begin(device);
    painter.setFont(QFont("Arial", 30));
    painter.setPen(QColor::fromRgb(255,255,255));
    painter.drawText(30,60,scoreStr);
    painter.end();
    glEnable(GL_DEPTH_TEST);
}

//SLOTS
void TetrisWidget::newGame()
{
    //call newgame from tetris (erase grid, generate new tetrominos)
    game.reset();
}

void TetrisWidget::rotate()
{
    if(canMove)
    {
        game.rotateRight();
        canMove = false;
        input_delay.start(delay);
    }
}

void TetrisWidget::goLeft()
{
    if(canMove)
    {
        game.goLeft();
        canMove = false;
        input_delay.start(delay);
    }
}

void TetrisWidget::goRight()
{
    if(canMove)
    {
        game.goRight();
        canMove = false;
        input_delay.start(delay);
    }
}

void TetrisWidget::fall()
{
    if(canMove)
    {
        game.fallDown();
        canMove = false;
        input_delay.start(delay);
    }
}

