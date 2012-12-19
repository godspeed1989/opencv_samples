#include "robert.h"
#include "cv.h"
#include "highgui.h"

int main()
{
    IplImage *src;
    //load img in gray scale
    src = cvLoadImage( "test.jpg", CV_LOAD_IMAGE_GRAYSCALE );
    cvNamedWindow( "src", 0 );
    cvShowImage( "src", src );

    IplImage* gray = cvCreateImage(cvGetSize(src), 8, 1);
    cvAdaptiveThreshold(src, gray, 255,
                        CV_ADAPTIVE_THRESH_GAUSSIAN_C,
                        CV_THRESH_BINARY,
                        71, 15);
    Robert( &gray );
    cvNamedWindow( "robert", 0 );
    cvShowImage( "robert", gray );

	IplImage *canny_img, *ncanny_img;
	canny_img = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	ncanny_img = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCanny(src, canny_img, 100, 200 , 3);
	cvNot(canny_img, ncanny_img);
	cvNamedWindow( "canny", 0 );
    cvShowImage( "canny", ncanny_img );
    cvWaitKey( 0 );
	
	cvReleaseImage(&src);
	cvReleaseImage(&gray);
	cvReleaseImage(&canny_img);
	cvReleaseImage(&ncanny_img);
    return 0;
}
