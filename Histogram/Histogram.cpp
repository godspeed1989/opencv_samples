#include <cv.h>
#include <highgui.h>
using namespace cv;

int main()
{
	int i;
	MatND hist;
	Mat image = imread("test.jpg", 0); // open in b&w
	
	/* Calculate the histogram */
#define DIM  1
	int channels = 0; // by default, we look at channel 0
	int hist_size[DIM] = { 256 };
	
	float hist_ranges[2*DIM];
	for(i=0; i<DIM; i++)
	{
		hist_ranges[i] = 0.0;
		hist_ranges[i+1] = 255.0;
	}
	const float *ranges[1] = { hist_ranges };
	calcHist(&image, 
			1,         // histogram from 1 image only
			&channels, // the channel used
			cv::Mat(), // no mask is used
			hist,      // the resulting histogram
			DIM,       // it is a 1D histgram (1 bin)
			hist_size, // number of bins
			ranges,    // pixel value range
			true,      // the histogram is uniform
			false	);
	
	/* Draw and display the histogram */
	double maxVal = 0;
	double minVal = 0;
	minMaxLoc(hist, &minVal, &maxVal, 0, 0);
	//image on which to display histogram
	Mat histImage(hist_size[0], hist_size[0], CV_8U, cv::Scalar(255));
	int hpt = static_cast<int>(0.9*hist_size[0]); // highest point is 90% of nbins
	for(int h=0; h<hist_size[0]; h++)
	{
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt/maxVal);
		line(histImage, Point(h, hist_size[0]),
						Point(h, hist_size[0]-intensity),
						Scalar::all(0));
	}
	namedWindow("Histogram", 0);
	imshow("Histogram", histImage);
	waitKey();
	return 0;
}
