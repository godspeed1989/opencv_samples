#include <cv.h>
#include <highgui.h>
using namespace cv;

int main()
{
	Mat src, hsv;
	src = imread("test.jpg", 1);
	cvtColor(src, hsv, CV_BGR2HSV);
	
	/* Calculate the Histogram */
	int hbins = 30; // Quantize hue to 30 levels
	int sbins = 32; // Quantize the saturation to 32 levels
	int histSize[] = {hbins, sbins};
	float hranges[] = {0, 180}; // hue varies from 0 to 179
	float sranges[] = {0, 256}; // saturation varies from 0 to 255
	const float* ranges[] = {hranges, sranges};
	MatND hist;
	int channels[] = {0, 1};
	calcHist(	&hsv,
				1,
				channels,// we look at channel 0 and 1
				Mat(),   // do not use mask
				hist,
				2,       // it is a 2D histgram (1 bin)
				histSize,
				ranges,
				true,    // the histogram is uniform
				false	);
	
	/* Show the Histogram */
	double maxVal=0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);
	int scale = 10;
	Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);
	for( int h = 0; h < hbins; h++ )
	{
		for( int s = 0; s < sbins; s++ )
		{
			float binVal = hist.at<float>(h, s);
			int intensity = cvRound(binVal*255/maxVal);
			rectangle( histImg, Point(h*scale, s*scale),
						Point( (h+1)*scale - 1, (s+1)*scale - 1),
						Scalar::all(intensity),
						CV_FILLED );
		}
	}
	
	namedWindow( "Source", 1 );
	imshow( "Source", src );
	namedWindow( "H-S Histogram", 1 );
	imshow( "H-S Histogram", histImg );
	waitKey();
	return 0;
}
