#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <time.h>
#include "bgfg_cb.h"
using namespace cv;
using namespace std;

vector<codeword> **cbMain;
vector<codeword> **cbCache;
int t=0;
int alpha = 10;
float beta =1;
int Tdel =50,Tadd = 50,  Th= 50;

//初始化大小
void initializeCodebook(int w,int h)
{
    cbMain = new vector<codeword>*[w];
    for(int i = 0; i < w; ++i)
        cbMain[i] = new vector<codeword>[h];

    cbCache = new vector<codeword>*[w];
    for(int i = 0; i < w; ++i)
        cbCache[i] = new vector<codeword>[h];
}

void update_cb(Mat& frame)
{
    if(t>20) return;
    for(int i=0;i<frame.rows;i++)
    {
        for(int j=0;j<frame.cols;j++)
        {
            int pix =  frame.at<uchar>(i,j);
            vector<codeword>& cm =cbMain[i][j];
            bool found = false;
            for(int k=0;k<cm.size();k++)
            {
                if(cm[k].min<=pix && pix<=cm[k].max && !found)
                {
                    found=true;
                    cm[k].min = ((pix-alpha)+(cm[k].f*cm[k].min))/(cm[k].f+1);//
                    cm[k].max = ((pix+alpha)+(cm[k].f*cm[k].max))/(cm[k].f+1);
                    cm[k].l=0;
                    cm[k].last=t;
                    cm[k].f++;
                }else
                {
                    cm[k].l++;
                }
            }
            if(!found)
            {
                codeword n={};
                n.min=max(0,pix-alpha);
                n.max=min(255,pix+alpha);
                n.f=1;
                n.l=0;
                n.first=t;
                n.last=t;
                cm.push_back(n);
            }
        }
    }
    t++;
}

void fg_cb(Mat& frame,Mat& fg)
{
    fg=Mat::zeros(frame.size(),CV_8UC1);
    if(cbMain==0) initializeCodebook(frame.rows,frame.cols);
    if(t<20)
    {
        update_cb(frame);
        return;
    }
   //训练模型
    for(int i=0;i<frame.rows;i++)
    {
        for(int j=0;j<frame.cols;j++)
        {
            int pix = frame.at<uchar>(i,j);
            vector<codeword>& cm = cbMain[i][j];
            bool found = false;
            for(int k=0;k<cm.size();k++)
            {
                if(cm[k].min<=pix && pix<=cm[k].max && !found)
                {
                    cm[k].min = ((1-beta)*(pix-alpha)) + (beta*cm[k].min);
                    cm[k].max = ((1-beta)*(pix+alpha)) + (beta*cm[k].max);
                    cm[k].l=0;
                    cm[k].first=t;
                    cm[k].f++;
                    found=true;
                }else
                {
                    cm[k].l++;
                }
            }
            //定期删除太久没出现的
            cm.erase(remove_if(cm.begin(), cm.end(), [](codeword& c) { return c.l>=Tdel;} ), cm.end());
            fg.at<uchar>(i,j) = found?0:255;
            if(found) continue;
            found = false;
            //cc存cb
            vector<codeword>& cc = cbCache[i][j];
            for(int k=0;k<cc.size();k++)
            {
                if(cc[k].min<=pix && pix<=cc[k].max && !found)
                {
                    cc[k].min = ((1-beta)*(pix-alpha)) + (beta*cc[k].min);
                    cc[k].max = ((1-beta)*(pix+alpha)) + (beta*cc[k].max);
                    cc[k].l=0;
                    cc[k].first=t;
                    cc[k].f++;
                    found=true;
                }else
                {
                    cc[k].l++;
                }
            }
            if(!found)
            {
                codeword n={};
                n.min=max(0,pix-alpha);
                n.max=min(255,pix+alpha);
                n.f=1;
                n.l=0;
                n.first=t;
                n.last=t;
                cc.push_back(n);
            }
            cc.erase(remove_if(cc.begin(), cc.end(), [](codeword& c) { return c.l>=Th;} ), cc.end());
            for(vector<codeword>::iterator it=cc.begin();it!=cc.end();it++)
            {
                if(it->f>Tadd)
                {
                    cm.push_back(*it);
                }
            }
            cc.erase( remove_if(cc.begin(), cc.end(), [](codeword& c) { return c.f>Tadd;} ), cc.end() );
        }
    }
}
