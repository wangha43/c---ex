#ifndef BGFG_CB_H
#define BGFG_CB_H
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <time.h>
using namespace cv;
using namespace std;


struct codeword {
    float min;
    float max;
    float f;
    float l;
    int first;
    int last;
    bool isStale;
};
extern int alpha ;
extern float beta ;
extern int Tdel ,Tadd , Th;


void initializeCodebook(int w,int h);
void update_cb(Mat& frame);
void fg_cb(Mat& frame,Mat& fg);
#endif // BGFG_CB_H

