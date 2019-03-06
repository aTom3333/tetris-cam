#include <opencv2/imgproc.hpp>
#include "VideoWidget.hpp"


using namespace cv;

VideoWidget::VideoWidget(QWidget* parent) : 
    QGraphicsView(parent),
    capture{new VideoCapture(0)}
{
    setScene(&scene);
    
    connect(&timer, &QTimer::timeout, [this]{
        if (capture->isOpened()) {
            Mat image;
            if (capture->read(image)) {   // Capture a frame
                // Flip to get a mirror effect
                flip(image,image,1);
                // Invert Blue and Red color channels
                cvtColor(image,image,CV_BGR2RGB);
                // Convert to Qt image
                QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
                scene.clear();
                scene.addPixmap(QPixmap::fromImage(img)); 
                
                update();
            }
        }
    });
    
    if(capture->isOpened())
    {
        timer.setInterval(1000 / capture->get(CAP_PROP_FPS));
        timer.start();
    }
}
