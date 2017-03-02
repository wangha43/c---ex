#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int largest_area_index=0;
CascadeClassifier haar_cascade;


void  refineSegments(Mat &img, Mat &mask, Mat &dst)
{
    int niters = 3;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat temp;
    Mat element;

     //9*9 area
    element = getStructuringElement(MORPH_RECT, Size(9, 9), Point(-1, -1));
    dilate(mask, temp, element, Point(4,4), niters);
    erode(temp, temp, element, Point(4,4), niters*2);
    dilate(temp, temp, element, Point(4,4), niters*3);
    threshold(temp, temp, 128, 255, CV_THRESH_BINARY);
     //optiopn question
    findContours( temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
   // dst = Mat::zeros(img.size(), CV_8UC3);
    if( contours.size() == 0)
        return;

    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect_<int> >  faceshoulders;
    Rect boundRect;
    int largest_area = 0;
    for(int i= 0;i<contours.size();i++){
         double a = contourArea(contours[i]);
        if(a>largest_area){
            largest_area=a;
            largest_area_index = i;
        }
    }
    haar_cascade.detectMultiScale(dst,faceshoulders);
    boundRect=boundingRect(contours[largest_area_index]);
    Scalar color = Scalar(0,0,255);
    rectangle(img,boundRect,color,1,8,0);
    rectangle(mask,boundRect,Scalar(255,255,255),1,8,0);
    for(size_t i =0;i<faceshoulders.size();i++){
        rectangle(img,faceshoulders[i],Scalar(0,255,0),1,8,0);
        cout << faceshoulders[i].x<<endl;
    }
}

int main()
{
    Mat tmp_frame,kframe,bgmask,back_frame;
        bool update_bg_model = true;
  Ptr<BackgroundSubtractorMOG2> bgsubtractor=createBackgroundSubtractorMOG2();
  bgsubtractor->setVarThreshold (30);
  haar_cascade.load("/root/opencv/opencv/data/haarcascades/haarcascade_upperbody.xml");
  VideoCapture cap(0);

  if(!cap.isOpened())
  {
    cout <<"\nCan not open camera or video file\n"<<endl;
      return -1;
  }
        for(;;)
        {
            cap >> tmp_frame;
            if( tmp_frame.empty() )
                break;

            //equalizeHist(kframe,kframe);
            blur(tmp_frame,kframe,Size(3,3),Point(-1,-1));
            cvtColor(kframe,kframe,CV_BGR2GRAY);
            bgsubtractor->apply(kframe, bgmask, update_bg_model ? -1 : 0);
            bgsubtractor->getBackgroundImage(back_frame);
            refineSegments(tmp_frame, bgmask, kframe);
            imshow("video", tmp_frame);
            imshow("foreground", bgmask);
            imshow("background",back_frame);
            int keycode = waitKey(30);
            if( keycode == 27 )
                break;
            if( keycode == ' ' )
            {
                update_bg_model = !update_bg_model;
                cout << "Learn background is in state ="<< update_bg_model << endl;
            }
        }

    return 0;
}
