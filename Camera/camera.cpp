#include <stdio.h>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>
#include "Detector.hpp"
#include "Image.hpp"
using namespace std;

const char * cascadefile = "haar_alt.txt";

int main(int, char**)
{
	cv::Mat frame, gray;
	cv::Scalar scalar(255, 255, 0, 0);
	cv::VideoCapture cap(0); // open the default camera
	if(!cap.isOpened()) // check if we succeeded
	{
		printf("Camera open error.\n");
		return -1;
	}
	cap >> frame; // get a new frame from camera
	
	u32 fps_cnt;
	clock_t start;
	char strFrame[64] = "0 fps";
	u32 w = frame.cols;
	u32 h = frame.rows;
	u32 size = w*h;
	printf("%d X %d\n", w, h);
	Image image(w, h);
	
	cv::Point pt1, pt2;
	Detector detect(cascadefile);
	
	cv::namedWindow("frame", 1);
	fps_cnt = 0;
	start = clock();
	for(;;)
	{
		cap >> frame; // get a new frame from camera
		cvtColor(frame, gray, CV_BGR2GRAY);
		for(u32 i=0; i<size; i++)
		{
			image.data[i] = gray.data[i];
		}
		vector<Rectangle> obj = detect.getObjects(image, 2, 1.4f, 0.2f, 1, 0);
		//cv::Mat img(h, w, CV_8UC4, image.data);
		cv::imwrite("result.jpg", gray);
		for(u32 i=0; i<obj.size(); i++)
		{
			pt1.x = obj[i].x;
			pt1.y = obj[i].y;
			pt2.x = pt1.x + obj[i].width;
			pt2.y = pt1.y + obj[i].height;
			cv::rectangle(frame, pt1, pt2, scalar, 2.5, 8, 0);
		}
		
		fps_cnt++;
		if(clock()-start > CLOCKS_PER_SEC)
		{
			sprintf(strFrame, "%d fps", fps_cnt);
			fps_cnt = 0;
			start = clock();
		}
		
		putText(frame, strFrame, cv::Point(0,20), 3, 1, CV_RGB(25,200,25));
		cv::imshow("frame", frame);
		if(cv::waitKey(30) >= 0) break;
	}
	return 0;
}

