#include "EqualizeHist.h"

#include "cv.h"
#include "highgui.h"

int main(int argc, char *argv[])
{
    const char *filename = "test.jpg";
    IplImage* src = cvLoadImage(filename , 1);
    if(!src)
        exit(-1);
    cvNamedWindow("source" , 0);
    cvShowImage("source" , src);

    IplImage* gray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
    cvCvtColor(src, gray, CV_RGB2GRAY);
    cvNamedWindow("gray result" , 0);
    cvShowImage("gray result" , gray);

    EqualizeHist(&gray);
    cvNamedWindow("Equalize gray result" , 0);
    cvShowImage("Equalize gray result" , gray);

    cvWaitKey(0);
    return 0;
}
