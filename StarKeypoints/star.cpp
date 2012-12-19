#include <cv.h>
#include <highgui.h>
#include <ctime>
#include <iostream>
using namespace std;
int main()
{
    IplImage * Image = NULL;
    CvMemStorage * storage = cvCreateMemStorage(0);
    Image = cvLoadImage("test.jpg", 0);

    cout<<(time(NULL))/1000<<endl;
    CvSeq* Keypoints = cvGetStarKeypoints(Image, storage);
    cout<<"Star Keypoints : "<<Keypoints->total<<endl;

    for(int i=0; i<Keypoints->total; i++)
    {
        CvStarKeypoint kpt;
        kpt = *(CvStarKeypoint*)cvGetSeqElem(Keypoints, i);
        int r = kpt.size/2;
        cvCircle(Image, kpt.pt, r, CV_RGB(0,255,0));
        cvLine(Image, cvPoint(kpt.pt.x+r, kpt.pt.y+r),  \
                      cvPoint(kpt.pt.x-r, kpt.pt.y-r),  \
                      CV_RGB(0,255,0));
        cvLine(Image, cvPoint(kpt.pt.x-r, kpt.pt.y+r),  \
                      cvPoint(kpt.pt.x+r, kpt.pt.y-r),  \
                      CV_RGB(0,255,0));
        cout<<"("<<kpt.pt.x<<","<<kpt.pt.y<<") ";
        cout<<"response "<<kpt.response<<endl;
    }
    cout<<(time(NULL))/1000<<endl;

    cvShowImage("Image", Image);
    cvWaitKey(0);
    return 0;
}
