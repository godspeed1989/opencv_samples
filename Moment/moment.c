#include <highgui.h>
#include <stdio.h>
#include <cv.h>

int main()
{
	IplImage *img , *bimg;
	
	//load a image as a gray image
	img = cvLoadImage("test.jpg", 0);
	//convert gray image to binary image
	bimg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U,1);
	cvAdaptiveThreshold(img, bimg, 255,
						CV_ADAPTIVE_THRESH_GAUSSIAN_C,
						CV_THRESH_BINARY,
						71, 15);
	
	//calc all the moments of the image
	CvMoments moments;
	cvMoments(img, &moments, 1);
	//get the seven hu moments
	CvHuMoments hu_moments;
	cvGetHuMoments(&moments, &hu_moments);

	printf("h1: %f\n", hu_moments.hu1);
	printf("h2: %f\n", hu_moments.hu2);
	printf("h3: %f\n", hu_moments.hu3);
	printf("h4: %f\n", hu_moments.hu4);
	printf("h5: %f\n", hu_moments.hu5);
	printf("h6: %f\n", hu_moments.hu6);
	printf("h7: %f\n", hu_moments.hu7);

	cvReleaseImage(&img);
	cvReleaseImage(&bimg);
	return 0;
}
