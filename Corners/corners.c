#include <cv.h>
#include <highgui.h>
#include <stdio.h>

#define max_corners 100

int main()
{
	int i;
	IplImage* srcImage=0,*grayImage=0,*corners1=0,*corners2=0;
	int cornerCount = max_corners;
	CvPoint2D32f corners[max_corners];
	double qualityLevel;
	double minDistance;
	
	CvScalar color = CV_RGB(255,0,0);
	
	srcImage = cvLoadImage("input.jpg", 1);
	grayImage = cvCreateImage(cvGetSize(srcImage), IPL_DEPTH_8U,1);
	cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
	
	cvGoodFeaturesToTrack(grayImage, NULL, NULL, corners, &cornerCount, \
							0.1, 5, NULL, 3, 0, 0.04);

	printf("num corners found: %d \n", cornerCount);
	
	if(cornerCount>0)
	{
		for(i=0; i<cornerCount; i++)
		{
			cvCircle(srcImage, cvPoint((int)(corners[i].x),(int)(corners[i].y)), 6, color, 2, CV_AA, 0);
		}
	}
	cvShowImage("Image", srcImage);
	
	cvReleaseImage(&srcImage);
	cvReleaseImage(&grayImage);
	cvWaitKey(0);
	return 0;
}
