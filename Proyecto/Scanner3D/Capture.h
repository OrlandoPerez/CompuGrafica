#ifndef CAPTURE_H
#define CAPTURE_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <vector>

#include <QWaitCondition>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class Capture : public QThread
{    Q_OBJECT
 private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage imgVideo;
     QImage imgFilter;

 signals:
    void processedImage(const QImage &image);

 protected:
     void run();
     void msleep(int ms);
 public:
    Capture(QObject *parent = 0);
    ~Capture();
    bool loadVideo(string filename);
    void Play();
    void Stop();
    bool isStopped() const;

    bool filterMode=false;

    vector<vector<QPoint>> mPoints;
};

#endif // CAPTURE_H
