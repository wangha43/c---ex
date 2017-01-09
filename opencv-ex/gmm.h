#ifndef GMM_H
#define GMM_H
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include <QObject>
#include <QThread>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
class gmm:public QObject
{
public:
    gmm();
    void init();
    void refineSegments(Mat& img, Mat& mask, Mat& dst);
    int largest_area_index ;
    CascadeClassifier haar_cascade;
    Ptr<BackgroundSubtractorMOG2> bgsubtractor;
private:
    QThread thread;
};

#endif // GMM_H
