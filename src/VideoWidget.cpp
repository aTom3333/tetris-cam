#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include "VideoWidget.hpp"

//turn into thread and live capture
using namespace cv;

VideoWidget::VideoWidget(QWidget* parent) : 
    QGraphicsView(parent),
    capture{new VideoCapture(0)}
{
    setScene(&scene);

    fist.loadCascade("../haarcascade/fistCascade.xml");

    connect(&timer, &QTimer::timeout, [this]{
        if (capture->isOpened()) {
            Mat image;
            if (capture->read(image)) {   // Capture a frame
                // Flip to get a mirror effect
                flip(image,image,1);
                // Invert Blue and Red color channels
                cvtColor(image,image,CV_BGR2RGB);

               fist.detectHand(image);
               fist.identifyHand();
               fist.drawLeftHand(image);
               fist.drawRightHand(image);
               fist.detectRotateByHand();
               fist.detectStrafeByHand();


                // Convert to Qt image
                QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);

                fist.detectFastFallByHand(img.height()/2);

                scene.clear();
                scene.addPixmap(QPixmap::fromImage(img)); 

                update();
            }
        }
    });
    
    if(capture->isOpened())
    {
        timer.setInterval(1000 / 60);
        timer.start();
    }
}

