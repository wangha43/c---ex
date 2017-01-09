#include "gmm.h"

gmm::gmm()
{

}

void gmm::init(){
    largest_area_index = 0;
    haar_cascade.load("/root/opencv/opencv/data/haarcascades/haarcascade_upperbody.xml");
    bgsubtractor=createBackgroundSubtractorMOG2();

    bgsubtractor->setVarThreshold(20);
    bgsubtractor->setDetectShadows(true);
    bgsubtractor->setShadowValue(0);
    moveToThread(&thread);
    thread.start();
}

void gmm::refineSegments(Mat &img, Mat &mask, Mat &dst)
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
