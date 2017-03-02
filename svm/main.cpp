#include <iostream>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect/detection_based_tracker.hpp"
#include "opencv2/objdetect/objdetect_c.h"
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>


using namespace std;
using namespace cv;
using namespace cv::ml;


int main()
{
    const int imgwidth = 140;
    const int imgheight = 180;
    string  file_path = "/home/wxc/svm/";
    string posi_file = file_path + "posi.txt";
    string neg_file = file_path + "nega.txt";
    string buff;
    //feature to compute and dimentions
    Mat sampleFeatureMat;
    Mat samplelableMat;
    int DescriptorDim;
        HOGDescriptor hog =HOGDescriptor(Size(64,128),Size(16,16),Size(8,8),Size(8,8),9);
    vector<string> file_path_array;
    vector<string> nega_path_array;
    ifstream read_img_file(posi_file);
    // read file path from txt file
    while(read_img_file){
        if(getline(read_img_file,buff)){
            file_path_array.push_back(buff);
        }
    }
    read_img_file.close();
    ifstream nega_img_file(neg_file);
    while(nega_img_file){
        if(getline(nega_img_file,buff)){
            nega_path_array.push_back(buff);
        }
    }
    nega_img_file.close();
    //initialize the svm class pointer;
    Ptr<SVM> svm = SVM::create();
    svm->setCoef0(0.0);
    svm->setDegree(3);
    svm->setTermCriteria(TermCriteria( CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 1e-3 ));
    svm->setGamma(0);
    svm->setKernel(SVM::LINEAR);
    svm->setNu(0.5);
    svm->setP(0.1); // for EPSILON_SVR, epsilon in loss function?
    svm->setC(0.01); // From paper, soft classifier
    svm->setType(SVM::EPS_SVR);
    //read images
    Mat src ;
    Mat trainimg = Mat::zeros(imgwidth,imgheight,CV_8UC3);
    for (size_t i =0;i<file_path_array.size();i++){
        src=imread(file_path_array[i]);
        if(src.empty()){
            cout <<"file can not open or existed" <<endl;
            continue;
        }
        resize(src,trainimg,Size(imgwidth,imgheight),0,0,INTER_CUBIC);
        trainimg = trainimg(Rect(16,16,84,128));
        vector <float> descriptor;
        //
        hog.compute(trainimg,descriptor,Size(8,8));
        if(i==0){
            DescriptorDim = descriptor.size();
            sampleFeatureMat = Mat::zeros(1000, DescriptorDim, CV_32FC1);
            samplelableMat = Mat::zeros(1000, 1, CV_32FC1);
        }
        for(int j=0; j<DescriptorDim; j++)
            sampleFeatureMat.at<float>(i,j) = descriptor[j];//
        samplelableMat.at<float>(i,0) = 1;
    }
    //read negative image files
    for (size_t i =0;i<nega_path_array.size();i++){
        src=imread(nega_path_array[i],1);
        if(src.empty()){
            cout <<"file can not open or existed" <<endl;
            continue;
        }
        resize(src,trainimg,Size(imgwidth,imgheight),0,0,INTER_CUBIC);
        trainimg = trainimg(Rect(16,16,84,128));
        vector <float> descriptor;
        //
        hog.compute(trainimg,descriptor,Size(8,8));

        for(int j=0; j<DescriptorDim; j++)
            sampleFeatureMat.at<float>(i,j) = descriptor[j];//
        samplelableMat.at<float>(i,0) = -1;
    }

    //    Ptr<TrainData> td = TrainData::create(trainingDataMat, ROW_SAMPLE, labelsMat);
    svm->train(sampleFeatureMat,ROW_SAMPLE,samplelableMat);
    //same svm
    svm->save("trainedSVM.xml");


    //    //Initialize SVM object
    //    Ptr<SVM> svmNew = SVM::create();
    //    //Load Previously saved SVM from XML

    //    svmNew = SVM::load<SVM>("trainedSVM.xml");



    //    Vec3b green(0, 255, 0), blue(255, 0, 0);
    //    // Show the decision regions given by the SVM
    //    for (int i = 0; i < image.rows; ++i)
    //        for (int j = 0; j < image.cols; ++j)
    //        {
    //            Mat sampleMat = (Mat_<float>(1, 2) << j, i);
    //            float response = svmNew->predict(sampleMat);

    //            if (response == 1)
    //                image.at<Vec3b>(i, j) = green;
    //            else if (response == -1)
    //                image.at<Vec3b>(i, j) = blue;
    //        }

    //    // Show the training data
    //    int thickness = -1;
    //    int lineType = 8;
    //    circle(image, Point(501, 10), 5, Scalar(0, 0, 0), thickness, lineType);
    //    circle(image, Point(255, 10), 5, Scalar(255, 255, 255), thickness, lineType);
    //    circle(image, Point(501, 255), 5, Scalar(255, 255, 255), thickness, lineType);
    //    circle(image, Point(10, 501), 5, Scalar(255, 255, 255), thickness, lineType);

    //    // Show support vectors
    //    thickness = 2;
    //    lineType = 8;
    //    Mat sv = svmNew->getSupportVectors();

    //    for (int i = 0; i < sv.rows; ++i)
    //    {
    //        const float* v = sv.ptr<float>(i);
    //        circle(image, Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thickness, lineType);
    //    }

    //    imwrite("result.png", image);        // save the image

    //    imshow("SVM Simple Example", image); // show it to the user
    //    waitKey(0);
    return(0);
}
