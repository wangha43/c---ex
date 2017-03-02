#include <QCoreApplication>
#include <QTextCodec>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"

#include <iostream>
#include <string>
#include "gmm.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
using namespace std;
using namespace cv;

gmm * Gauss = new gmm;
int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    qDebug("av init");
    av_register_all();
    avformat_network_init();

    Gauss->init();
    VideoCapture cap(0);


    if(!cap.isOpened())
    {
      cout <<"\nCan not open camera or video file\n"<<endl;
        return -1;
    }
    Mat tmp_frame, bgmask, out_frame,kframe,back_frame;
    namedWindow("video", 1);
    namedWindow("foreground", 1);

   // bgsubtractor->setShadowThreshold(10);
    /*
     *using haar cascade detect face and shoulder
     *
     */

//    for(;;)
//    {
//        cap >> tmp_frame;
//        if( tmp_frame.empty() )
//            break;

//        //equalizeHist(kframe,kframe);
//        blur(tmp_frame,kframe,Size(3,3),Point(-1,-1));
//        cvtColor(kframe,kframe,CV_BGR2GRAY);
//        bgsubtractor->apply(kframe, bgmask, update_bg_model ? -1 : 0);
//        bgsubtractor->getBackgroundImage(back_frame);
//        Gauss->refineSegments(tmp_frame, bgmask, kframe);
//        imshow("video", tmp_frame);
//        imshow("foreground", bgmask);
//        imshow("background",back_frame);
//        int keycode = waitKey(30);
//        if( keycode == 27 )
//            break;
//        if( keycode == ' ' )
//        {
//            update_bg_model = !update_bg_model;
//            cout << "Learn background is in state ="<< update_bg_model << endl;
//        }
//    }
//    return 0;
    AVFormatContext* context = avformat_alloc_context();
    int video_stream_index=-1;
    AVDictionary *avdic=NULL;
    av_dict_set(&avdic,"rtsp_transport","tcp",0);
    av_dict_set(&avdic,"stimeout","1000000",0);
    av_dict_set(&avdic,"max_delay","50000",0);
    av_dict_set(&avdic,"fflags","nobuffer",0);
    av_dict_set(&avdic,"allowed_media_types","video",0);
    context->flags=AVFMT_FLAG_NOBUFFER;
    //open rtsp
    if(avformat_open_input(&context,"rtsp://admin:admin@192.168.3.60:554/cam/realmonitor?channel=1&subtype=0",NULL,&avdic) != 0){
        qDebug("can not open rtsp ");
        avformat_free_context(context);
    }
    if(avformat_find_stream_info(context,NULL) < 0){
        qDebug("can not find rtsp info");
        avformat_free_context(context);
    }

    for(int i =0;i<context->nb_streams;i++){
        if(context->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream_index = i;
        }
    }
    AVPacket *packet=new AVPacket();
    av_init_packet(packet);
    av_read_play(context);

    AVCodecID codec_id=AV_CODEC_ID_H264;
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx= NULL;
    AVCodecParserContext *pCodecParserCtx=NULL;
    AVFrame *pFrame;


    pCodec = avcodec_find_decoder(codec_id);
    if (!pCodec) {
        qDebug("Codec not found");
        return -1;
    }
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if (!pCodecCtx){
        qDebug("Could not allocate video codec context");
        return -1;
    }

    pCodecParserCtx=av_parser_init(codec_id);
    if (!pCodecParserCtx){
        qDebug("Could not allocate video parser context");
        return -1;
    }
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug("Could not open codec");
        return -1;
    }

    int ret,got_picture;
    bool waitkey=true;
    pFrame = avcodec_alloc_frame() ;
    cvNamedWindow("video", 1);
//    cv::Mat buf;
//    Test test;
//    QThread thread;
//    test.moveToThread(&thread);
//    thread.start();
    int count=0;
    while(av_read_frame(context,packet)>=0)
    {
        if(waitkey)
        {
            if(packet->flags==1)
                waitkey=false;
            else
                continue;

        }

        ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
        if (ret < 0) {
            qDebug("Decode Error.");
            continue;
        }
        if (got_picture) {

            count++;
            count=count%15;
            if(count!=0)
            {
                av_free_packet(packet);
                continue;
            }
            Mat kframe,bgmask,back_frame;
            Mat tmp_frame(pFrame->height, pFrame->width, CV_8UC1, pFrame->data[0], pFrame->linesize[0]);
    //processing
            blur(tmp_frame,kframe,Size(3,3),Point(-1,-1));

            Gauss->bgsubtractor->apply(kframe, bgmask, true ? -1 : 0);
            Gauss->bgsubtractor->getBackgroundImage(back_frame);

            Gauss->refineSegments(tmp_frame, bgmask, kframe);
  //
//                if(tracker_sys == true){
//          track(boundRect,tmp_frame);
//                }
//            Mat descriptors_1;
//            detector->compute( tmp_frame, keyPoint1, descriptors_1 );
//            drawKeypoints(tmp_frame,keyPoint1,draw);

            cv::Mat frame(720, 1280, CV_8UC1);
            for(int i=0;i<720;i++)
            {
                memcpy(frame.data+i*1280,pFrame->data[0]+i*pFrame->linesize[0],1280);
            }
            imshow("video", tmp_frame);
            imshow("foreground", bgmask);
            imshow("background",back_frame);
            IplImage img = (IplImage)(frame);

            cvShowImage("video",&img);
            cvWaitKey(1);
            qDebug("got video");
        }

        av_free_packet(packet);
    }
    return a.exec();
}
