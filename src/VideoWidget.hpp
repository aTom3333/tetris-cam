#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <QGraphicsView>
#include <QTimer>

#include <memory>

#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include "opencv2/video.hpp"


class VideoWidget : public QGraphicsView
{
public:
    explicit VideoWidget(QWidget* parent = nullptr);
    
private:
    std::unique_ptr<cv::VideoCapture> capture;
    QTimer timer;
    QGraphicsScene scene;
};


#endif // VIDEOWIDGET_HPP
