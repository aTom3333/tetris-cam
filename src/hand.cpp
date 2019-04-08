#include "hand.h"
#include <QThread>
#include <QDebug>

Hand::Hand(){
    connect(&timerOfRightHandPresence_, SIGNAL(timeout()), this, SLOT(rightHandDisapear()));
    connect(&timerOfLeftHandPresence_, SIGNAL(timeout()), this, SLOT(leftHandDisapear()));
}

void Hand::leftHandDisapear(){
    qDebug()<<"left is no longer present";
    isLeftHand = false;
    this->timerOfLeftHandPresence_.stop();
}

void Hand::rightHandDisapear(){
    qDebug()<<"right is no longer present";
    isRightHand = false;
    this->timerOfRightHandPresence_.stop();
}

bool Hand::loadCascade(std::string path){
    cascade_.load(path);
    if(cascade_.empty())
        return false;
    return true;
}

void Hand::detectHand(cv::Mat& frame){
    //trouve toutes les mains dans l'image
    cascade_.detectMultiScale(frame, hands_, 1.3, 4, 0, cv::Size(20, 20));
}

//choisie deux main pour les elirent mains droite/gauche
void Hand::identifyHand()
{
    if(hands_.size() !=0){
        cv::Rect leftHandTEMP = hands_[0];
        cv::Rect rightHandTEMP = hands_[0];

        //definie main droite/gauche par l'ecart minimum par rapport à la précedente detection
        for(size_t i=1; i<hands_.size();i++){

            //si l'ecart est plus court que la precedente election cette main à plus de chance d'etre la vrai main
            if(abs(hands_[i].x - leftHand_.x) < abs(leftHandTEMP.x - leftHand_.x)){
                leftHandTEMP = hands_[i];
            }

            //de meme pour gauche
            if(abs(hands_[i].x - rightHand_.x) < abs(rightHandTEMP.x - rightHand_.x)){
                rightHandTEMP = hands_[i];
            }
        }

        //si main gauche/droite sont les meme il nous maque une main
        //on trouve a quelle main precedament identifier ce raproche le plus la main detecter
        if(leftHandTEMP == rightHandTEMP){

            //si l'ecart entre l'election gauche et la precedente position de main gauche et plus
            //faible que pour la droite alors la main detecter est la gauche
            if(abs(leftHandTEMP.x - leftHand_.x) < abs(rightHandTEMP.x - rightHand_.x)){
                leftHand_ = leftHandTEMP;
                timerOfLeftHandPresence_.stop(); //on l'a trouver donc on stop le timer d'absence
                isLeftHand = true;

                //si la main droite disparait pour la premiere fois on active le timer d'absence
                if(!timerOfRightHandPresence_.isActive() && isRightHand){
                    qDebug()<<"right has disapear";
                     timerOfRightHandPresence_.start(500);
                }
            }else {
                rightHand_ = rightHandTEMP;
                timerOfRightHandPresence_.stop(); //on l'a trouver donc on stop le timer d'absence
                isRightHand = true;
                //si cette main disparait pour la premiere fois
                if(!timerOfLeftHandPresence_.isActive() && isLeftHand){
                    timerOfLeftHandPresence_.start(500);
                    qDebug()<<"left has disapear";
                }
            }
        }
        else{ //si les deux main sont differentes alors tout va bien
            leftHand_ = leftHandTEMP;
            rightHand_ = rightHandTEMP;
            isLeftHand = true;
            isRightHand = true;
            timerOfLeftHandPresence_.stop();
            timerOfRightHandPresence_.stop();
        }
   }
    //si aucune main n'est détecté
   else{
        //si le timer n'est pas actif et que la main est presente on lance le timer d'absence
        if(!timerOfLeftHandPresence_.isActive() && isLeftHand){
            timerOfLeftHandPresence_.start(500);
            qDebug()<<"no hand detected but left present, starting timer";
        }
        if(!timerOfRightHandPresence_.isActive() && isRightHand){
            timerOfRightHandPresence_.start(500);
            qDebug()<<"no hand detected but right present, starting timer";
        }
    }
}

void Hand::drawAllBoundingBox(cv::Mat& frame, const cv::Scalar color, const std::string text) const
{
    if (hands_.size() != 0) {
        for (size_t i = 0; i < hands_.size(); i++) {
            // Top left and bottom right points of rectangle.
            cv::Point closed_palm_rect_p1(hands_[i].x, hands_[i].y);
            cv::Point closed_palm_rect_p2(hands_[i].x + hands_[i].width, hands_[i].y + hands_[i].height);

            // Draw the rectangle in the image.
            rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, color);
            putText(frame, text, closed_palm_rect_p1, cv::FONT_HERSHEY_SIMPLEX,
                    1, color, 1, 5, false);
        }
    }
}

void Hand::drawLeftHand(cv::Mat& frame, const cv::Scalar color, const std::string text) const
{
    if(isLeftHand){
        // Top left and bottom right points of rectangle.
        cv::Point closed_palm_rect_p1(leftHand_.x, leftHand_.y);
        cv::Point closed_palm_rect_p2(leftHand_.x + leftHand_.width, leftHand_.y + leftHand_.height);

        // Draw the rectangle in the image.
        rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, color);
        putText(frame, text, closed_palm_rect_p1, cv::FONT_HERSHEY_SIMPLEX,
                1, color, 1, 5, false);
    }
}

void Hand::drawRightHand(cv::Mat& frame, const cv::Scalar color, const std::string text) const
{
    if(isRightHand){
        // Top left and bottom right points of rectangle.
        cv::Point closed_palm_rect_p1(rightHand_.x, rightHand_.y);
        cv::Point closed_palm_rect_p2(rightHand_.x + rightHand_.width, rightHand_.y + rightHand_.height);

        // Draw the rectangle in the image.
        rectangle(frame, closed_palm_rect_p1, closed_palm_rect_p2, color);
        putText(frame, text, closed_palm_rect_p1, cv::FONT_HERSHEY_SIMPLEX,
                1, color, 1, 5, false);
    }
}

void Hand::detectRotateByHand()
{
    //il nous faut les deux mains
    if(isRightHand && isLeftHand){

        //on verifie que l'ecart entre les deux mains est inférieur à la moitier de la main (seuil)
        if(abs(leftHand_.x +leftHand_.width - rightHand_.x) < leftHand_.width/2){

            qDebug()<<"touché";
            emit rotate();
        }
    }
}

void Hand::detectStrafeByHand()
{
    //il nous faut les deux mains
    if(isRightHand && isLeftHand){

        //on verifie que l'ecart verticale entre les deux mains est supérieur à la moitier de la main (seuil)
        if(abs(leftHand_.y - rightHand_.y) > leftHand_.height/2){

            //Si la main gauche est plus haute que la droite
            if(leftHand_.y < rightHand_.y){
                qDebug()<<"stafe right";
                emit strafeRight();
            }
            else{
                qDebug()<<"stafe left";
                emit strafeLeft();
            }
        }
    }
}

void Hand::detectFastFallByHand(int seuilY)
{
    //il nous faut les deux mains
    if(isRightHand && isLeftHand){

        //si les deux main sont en dessous du seuil
        if(leftHand_.y > seuilY && rightHand_.y > seuilY){
            qDebug()<<"fast fall";
            emit fastFall();
        }
    }
}


