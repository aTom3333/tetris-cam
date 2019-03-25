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
    
    gluLookAt(-2, -15, 10, 0, 0, 0, 0, 1, 0);
    
    glRotated(10,0,0,1);

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

    //dessin des cube de la grille

}

void TetrisWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();
    
    // Reglage de la couleur de fond
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
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

//void TetrisWidget::drawCubes()
//{
//    for(size_t i =0; i<grille.size();i++){
//        for (size_t j=0;j< grille[i].size();j++) {

//        glBegin(GL_QUADS);

//        //fct applicage de texture en fct de grille[][]
//            glColor3ub(0, 0, 255); //face avant bleu
//            glVertex3f(j-radius, i-radius, radius);
//            glVertex3f(j+radius, i-radius, radius);
//            glVertex3f(j+radius, i+radius, radius);
//            glVertex3f(j-radius, i+radius, radius);

//            //jamais dessiner
// //            glColor3ub(255, 0, 255); //face arriere rose
// //            glVertex3f(j-radius, i-radius, -radius);
// //            glVertex3f(j+radius, i-radius, -radius);
// //            glVertex3f(j+radius, i+radius, -radius);
// //            glVertex3f(j-radius, i+radius, -radius);

//            if(!contain(j-1,i)){
//                glColor3ub(255, 0, 0); //face coter gauche rouge
//                glVertex3f(j-radius, i-radius, radius);
//                glVertex3f(j-radius, i+radius, radius);
//                glVertex3f(j-radius, i+radius, -radius);
//                glVertex3f(j-radius, i-radius, -radius);
//            }

//            if(!contain(j+1,i)){
//                glColor3ub(255, 255, 0); //face coter droite jaune
//                glVertex3f(j+radius, i-radius, radius);
//                glVertex3f(j+radius, i+radius, radius);
//                glVertex3f(j+radius, i-radius, -radius);
//                glVertex3f(j+radius, i+radius, -radius);
//            }

//            if(!contain(j,i-1)){
//                glColor3ub(0, 255, 0); //face dessus verte
//                glVertex3f(j+radius, i+radius, radius);
//                glVertex3f(j-radius, i+radius, radius);
//                glVertex3f(j-radius, i+radius, -radius);
//                glVertex3f(j+radius, i+radius, -radius);
//            }


//            if(!contain(j,i+1)){
//                glColor3ub(0, 255, 255); //face dessous cyan
//                glVertex3f(j+radius, i-radius, radius);
//                glVertex3f(j-radius, i-radius, radius);
//                glVertex3f(j+radius, i-radius, -radius);
//                glVertex3f(j-radius, i-radius, -radius);
//            }

//            glEnd();

//        }
//    }
//}

//bool TetrisWidget::contain(int x, int y)
//{
//    if(grille[y][x] != 0){return false;}
//    else{return true;}
//}
