#include "cv.h"
#include "highgui.h"
#include <stdio.h>

int main()
{
    //----------------Load & Show a gray img---------------------//
    IplImage* img = cvLoadImage("test.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    if(!img)
        exit(-1);
    cvNamedWindow("Oringin" , 0);
    cvShowImage("Oringin" , img);

    //--------------------Threshold Image------------------------//
    double threshold = 125;
    ////////////Binary Threshold Image///////////

    IplImage* th_img_bin = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
    if(!th_img_bin)
        exit(-3);
    cvNamedWindow("Threshold_Binary" , 0);
    cvThreshold(img, th_img_bin, threshold , 255, CV_THRESH_BINARY);
    cvShowImage("Threshold_Binary" , th_img_bin);

    ///////////Adaptive Threshold Image///////////
    IplImage* ath_img = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U , 1);
    if(!ath_img)
        exit(-4);
    cvNamedWindow("Adaptive_Threshold" , 0);
    cvAdaptiveThreshold(img, ath_img, 255,
                        CV_ADAPTIVE_THRESH_GAUSSIAN_C,//adaptive method
                        CV_THRESH_BINARY, //threshold type
                        71, //block size
                        15);//offset
    cvShowImage("Adaptive_Threshold" , ath_img);

    cvWaitKey(0);
    return 0;
}

