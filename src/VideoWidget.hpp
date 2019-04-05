#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <QGraphicsView>
#include <QTimer>

#include <memory>

#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include "opencv2/video.hpp"
#include "Tetris/hand.h";

//Class représentant la partie openCv du projet.
//On n'y retrouve la video de la caméra et
//la detection des mains.
//Auteur : Axel POULAT
class VideoWidget : public QGraphicsView
{
public:
//constructeur
    explicit VideoWidget(QWidget* parent = nullptr);
    
private:
//pointeur sur la class gérant la video de la caméra
    std::unique_ptr<cv::VideoCapture> capture;
//timer pour rafraichir l'image affiché
    QTimer timer;
//scene graphique où l'image est dessiné 
    QGraphicsScene scene;
//class gérant la detection des mains
    Hand fist;
};


#endif // VIDEOWIDGET_HPP
