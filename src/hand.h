#ifndef HAND_H
#define HAND_H
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QWidget>
#include <QTimer>

class Hand : public QObject
{
        Q_OBJECT
private:
    cv::CascadeClassifier cascade_;
    std::vector<cv::Rect> hands_;
    cv::Rect leftHand_;
    cv::Rect rightHand_;
    QTimer timerOfRightHandPresence_;
    bool isRightHand = false;
    QTimer timerOfLeftHandPresence_;
    bool isLeftHand = false;

 private slots:
    void leftHandDisapear();
    void rightHandDisapear();

public:
    Hand();
    bool loadCascade(const std::string path);
    void detectHand(cv::Mat& frame);
    void identifyHand();
    void drawAllBoundingBox(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "HAND") const;
    void drawLeftHand(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "LEFT HAND") const;
    void drawRightHand(cv::Mat& frame, const cv::Scalar color = cv::Scalar(0,255,0), const std::string text = "RIGHT HAND") const;
    void detectRotateByHand();
    void detectStrafeByHand();
    void detectFastFallByHand(int seuilY);


signals :
    void rotate();
    void strafeLeft();
    void strafeRight();
    void fastFall();
};

#endif // HAND_H
