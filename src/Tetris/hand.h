#ifndef HAND_H
#define HAND_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QWidget>
#include <QTimer>


//Class gerant la detection des mains et l'envois de signals 
//lorsque l'utilisateur effectue des actions
//Auteur : Axel POULAT
class Hand : public QObject
{
        Q_OBJECT
private:
//Le Haarcascade pour detecter les mains
    cv::CascadeClassifier cascade_;
	
//stoque tout les "mains" trouvées par le haar
    std::vector<cv::Rect> hands_;
	
//la vraie main gauche/droite
    cv::Rect leftHand_;
    cv::Rect rightHand_;
	
//les timer d'absence des mains permettent de sauvegarder la position 
//des mains pendant un temps fixe lorsque elles ne sont plus detectées
//cela rend la detection plus robuste au prix d'un temps de réaction
//les booleans sont la pour acter de la presence ou non des mains
    QTimer timerOfRightHandPresence_;
    bool isRightHand = false;
    QTimer timerOfLeftHandPresence_;
    bool isLeftHand = false;

//Slot permettant de metre les booleans a faux lorsque 
//les timers sont expirées
 private slots:
    void leftHandDisapear();
    void rightHandDisapear();

public:
	//constructeur
    Hand();
	//load le fichier Haarcascade
    bool loadCascade(const std::string path);
	//detecte toutes les "mains" sur l'images
    void detectHand(cv::Mat& frame);
	//identifie la vraie main gauche/droite
    void identifyHand();
	//dessine les carrés de detections des "mains"
    void drawAllBoundingBox(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "HAND") const;
    //dessine les carrés de detections des vraie mains
	void drawLeftHand(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "LEFT HAND") const;
    void drawRightHand(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "RIGHT HAND") const;
    //detecte les commandes utilisateur
	void detectRotateByHand(); //rotation
    void detectStrafeByHand(); //translation droite/gauche
    void detectFastFallByHand(int seuilY); //descente rapide

//les signaux emis lors des commandes utilisateurs
signals :
    void rotate();
    void strafeLeft();
    void strafeRight();
    void fastFall();
};

#endif // HAND_H
