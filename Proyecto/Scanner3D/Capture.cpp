#include "Capture.h"
#include <vector>
#include <iostream>


using namespace std;


Capture::Capture(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

bool Capture::loadVideo(string filename) {
    capture.open(filename);
    if (capture.isOpened())
    {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}

void Capture::Play()
{
    if (!isRunning()) {
        if (isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}

void Capture::run()
{
    TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
    //Size subPixWinSize(10,10), winSize(31,31);
    int delay = (1000/frameRate);
    vector<Point2f> points[2];

    // detect white
    int iLowH = 0;
     int iHighH = 180;

      int iLowS = 0;
     int iHighS = 4.5;

      int iLowV = 245;
     int iHighV = 255;



    while(!stop){
        if (!capture.read(frame))
        {
            stop = true;
        }


        else if (frame.channels()== 3){
                //RGBframe= Scalar::all(0);

                cv::cvtColor(frame, RGBframe, CV_BGR2HSV);

                Mat imgThresholded;


                inRange(RGBframe, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);

                //edges
                Mat canny_output;
                int thresh = 100;
                //int max_thresh = 255;

                Canny(imgThresholded , canny_output, thresh, thresh*2, 3 );



                 Mat edges= Mat::zeros( canny_output.size(), CV_8UC3 );


                vector<Point> locations;  // output, locations of non-zero pixels
                findNonZero(canny_output, locations);


                vector <QPoint> points;
                for(unsigned int i=0; i< locations.size(); i++ ){
                    Scalar color(255,255,255);
                    drawMarker( edges, locations[i], color, CV_FILLED, 1);
                    points.push_back( QPoint(locations[i].x,locations[i].y));
                }

                mPoints.push_back(points);

                if (filterMode)
                    imgVideo = QImage((const unsigned char*)(edges.data),edges.cols,edges.rows,QImage::Format_RGB888);
                else{
                    cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
                    imgVideo = QImage((const unsigned char*)(RGBframe.data),RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
                }


        }
        else
        {
            imgVideo = QImage((const unsigned char*)(frame.data),
                                 frame.cols,frame.rows,QImage::Format_Indexed8);
        }

        emit processedImage(imgVideo);
        this->msleep(delay);
    }
}

Capture::~Capture()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void Capture::Stop()
{
    stop = true;
}
void Capture::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}
bool Capture::isStopped() const{
    return this->stop;
}
