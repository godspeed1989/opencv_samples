#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <stdio.h>

using namespace cv;
int main(int argc, char** argv)
{
	Mat image;
	image = imread("board.jpg", 0);
	// smooth it, otherwise a lot of false circles may be detected
	GaussianBlur( image, image, Size(9, 9), 2, 2 );
	vector<Vec3f> circles;
	HoughCircles(image,
				circles,
				CV_HOUGH_GRADIENT,
				2,
				10,
				100, 50,
				1, 30 );
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle( image, center, 3, Scalar(0,255,0), -1, 8, 0 );
		circle( image, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}
	namedWindow( "circles", 1 );
	imshow( "circles", image );
	waitKey();
	return 0;
}

