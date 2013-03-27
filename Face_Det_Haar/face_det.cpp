#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void detect_face( Mat& img,
                  CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
                  double scale );

int main()
{
	Mat image;
	CascadeClassifier cascade;
	cascade.load("haarcascade_frontalface_alt.xml");
	CascadeClassifier nestedCascade;
	nestedCascade.load("haarcascade_eye_tree_eyeglasses.xml");
	
	VideoCapture cap(0); // open the default camera
	namedWindow("face", 1);
	double scale = 1.5;
	if(0)
	{
		image = imread( "faceScene.jpg", 1 );
		detect_face(image, cascade, nestedCascade, scale);
	}
	else
	{
		for(;;)
		{
			cap >> image;
			detect_face(image, cascade, nestedCascade, scale);
			imshow("face", image);
			if(cv::waitKey(30) >= 0) break;
		}
	}
	return 0;
}

void detect_face( Mat& img,
                  CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
                  double scale )
{
    int i = 0;
    double t = 0;
    vector<Rect> faces;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
    // resize image
    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );
    
    //cout<<"Detect and draw face(s)"<<endl;
    t = (double)cvGetTickCount();
    cascade.detectMultiScale( smallImg, faces,
                             1.1, 2, 0
                             //|CV_HAAR_FIND_BIGGEST_OBJECT
                             //|CV_HAAR_DO_ROUGH_SEARCH
                             |CV_HAAR_SCALE_IMAGE
                             ,
                             Size(30, 30) );
    t = (double)cvGetTickCount() - t;
    //printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Rect rect;
        Scalar color = colors[i%8];
        int radius;
        center.x = cvRound((r->x + r->width*0.5)*scale);
        center.y = cvRound((r->y + r->height*0.5)*scale);
        radius = cvRound((r->width + r->height)*0.25*scale);
        circle( img, center, radius, color, 3, 8, 0 );
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg(*r);
        
        rect = *r;
        rect.x = cvRound((r->x)*scale);
        rect.y = cvRound((r->y)*scale);
        rectangle( img, rect, CV_RGB(0,0,0), 3, 8, 0);
        
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
                                       1.1, 2, 0
                                       //|CV_HAAR_FIND_BIGGEST_OBJECT
                                       //|CV_HAAR_DO_ROUGH_SEARCH
                                       //|CV_HAAR_DO_CANNY_PRUNING
                                       |CV_HAAR_SCALE_IMAGE
                                       ,
                                       Size(30, 30) );
        for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
        {
            center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
            center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
            radius = cvRound((nr->width + nr->height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
    }
    imwrite("result.jpg", img);
}

