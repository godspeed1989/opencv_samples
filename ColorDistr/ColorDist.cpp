#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <iostream>
using namespace std;

double ColorDist(IplImage* img1, IplImage* img2, int release)
{
    assert(img1!=NULL && img2!=NULL);
    //for img1
    IplImage *h_plane1, *s_plane1;
    h_plane1 = cvCreateImage(cvGetSize(img1), 8, 1);
    s_plane1 = cvCreateImage(cvGetSize(img1), 8, 1);
    cvCvtPixToPlane(img1, h_plane1, s_plane1, 0, 0);
    IplImage* planes1[] = {h_plane1, s_plane1};
    //for img2
    IplImage *h_plane2, *s_plane2;
    h_plane2 = cvCreateImage(cvGetSize(img2), 8, 1);
    s_plane2 = cvCreateImage(cvGetSize(img2), 8, 1);
    cvCvtPixToPlane(img2, h_plane2, s_plane2, 0, 0);
    IplImage* planes2[] = {h_plane2, s_plane2};
    ////////////////////////////////////
    int h_size = 12;
    int s_size = 14;
    int size[] = {h_size, s_size};
    float h_range[] = {0,180};
    float s_range[] = {0,255};
    float* range[] = {h_range, s_range};
    CvHistogram *hist1, *hist2;
    hist1 = cvCreateHist(2, size, CV_HIST_ARRAY, range, 1);
    cvCalcHist(planes1, hist1, 0, NULL);
    hist2 = cvCreateHist(2, size, CV_HIST_ARRAY, range, 1);
    cvCalcHist(planes2, hist2, 0, NULL);
    /*
      CV_COMP_CORREL
      CV_COMP_CHISQR
      CV_COMP_INTERSECT
      CV_COMP_BHATTACHARYYA
    */
    double tmp;
    tmp = cvCompareHist(hist1, hist2, CV_COMP_CORREL);
    /*************************************/
    if(release)
    {
        cvReleaseImage(&img1);
        cvReleaseImage(&img2);
    }
    cvReleaseImage(&h_plane1);
    cvReleaseImage(&s_plane1);
    cvReleaseImage(&h_plane2);
    cvReleaseImage(&s_plane2);
    cvReleaseHist(&hist1);
    cvReleaseHist(&hist2);
    /*************************************/
    return tmp;
}

#define NUM 2

int main()
{
	double count1, count2, m;
	char file1[16];
	char file2[16];
	count1 = 0;
	for(int i=1 ; i<=NUM*2 ; i+=2)
	{
		sprintf(file1, "g%d.jpg", i);
		sprintf(file2, "g%d.jpg", i+1);
		IplImage* img1 = cvLoadImage(file1);
		IplImage* img2 = cvLoadImage(file2);
		assert(img1 != NULL && img2 != NULL);
		m = ColorDist(img1, img2, 1);
		count1 += m;
		cout<<i<<" <-> "<<i+1<<" diff "<<m<<endl;
	}
	cout<<"avg = "<<count1/NUM<<endl;
	cout<<"-----------------------"<<endl;
	count2 = 0;
	for(int i=1 ; i<=NUM ; i++)
	{
		sprintf(file1, "g%d.jpg", i);
		sprintf(file2, "g%d.jpg", i+NUM);
		IplImage* img1 = cvLoadImage(file1);
		IplImage* img2 = cvLoadImage(file2);
		assert(img1 != NULL && img2 != NULL);
		m = ColorDist(img1, img2, 1);
		count2 += m;
		cout<<i<<" <-> "<<i+NUM<<" diff "<<m<<endl;
	}
	cout<<"avg = "<<count2/NUM<<endl;

	return 0;
}
