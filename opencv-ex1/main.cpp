#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "bgfg_cb.h"
#include <iostream>
using namespace cv;
using namespace std;

CascadeClassifier haar_cascade;
void proc()
{
    Mat frame,fg,gray;
    VideoCapture cap(0);
    cap >> frame;
    initializeCodebook(frame.rows,frame.cols);
    for(;;)
    {
        cap>>frame;
        cvtColor(frame,gray,CV_BGR2GRAY);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        vector<Rect_<int> >  faceshoulders;
        fg_cb(gray,fg);
       // Mat cc;
//        erode(fg,fg,Mat(),Point(-1,-1),2);
//        dilate(fg,fg,Mat(),Point(-1,-1),2);
//        findContours(fg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
//        if( contours.size() != 0){
//            int largest_area = 0;
//            int largest_area_index=0;
//            for(size_t i= 0;i<contours.size();i++){
//                double a = contourArea(contours[i]);
//                if(a>largest_area){
//                    largest_area=a;
//                    largest_area_index = i;
//                }
//            }
//            Rect boundRect =boundingRect(contours[largest_area_index]);
//            rectangle(frame,boundRect,Scalar(255,255,255),1);
//        }
//        haar_cascade.detectMultiScale(frame,faceshoulders);
//        if(faceshoulders.size()!=0){
//            for(size_t i =0;i<faceshoulders.size();i++){
//                rectangle(frame,faceshoulders[i],Scalar(0,255,0),1,8,0);
//                //cout << faceshoulders[i].x<<endl;
//            }
//        }

        imshow("frame",frame);
        imshow("fg",fg);
        waitKey(1);
      }
}

int main(int argc, char ** argv)
{
    haar_cascade.load("/home/wxc/Downloads/haarcascade_upperbody.xml");
    proc();
    cin.ignore(1);
    return 0;
}
