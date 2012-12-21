#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <stdlib.h>
using namespace cv;
// A simple linear SVM example
int main()
{
	int width = 512, height = 512;
	Mat image = Mat::zeros(height, width, CV_8UC3);
	
	// Set up training data
#define NUM 5
	float labels[NUM] = {1.0, 1.0, -1.0, -2.0, -1.0};
	Mat labelsMat(NUM, 1, CV_32FC1, labels);
	float trainingData[NUM][2] = { {450, 10}, {420, 25},
						{250, 50}, {450, 250}, {10, 450} };
	Mat trainingDataMat(NUM, 2, CV_32FC1, trainingData);
	
	/* Set up SVM's parameters and Train SVM */
	CvSVM SVM;
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC;
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
	SVM.train(trainingDataMat, labelsMat, Mat(), Mat(), params);
	
	// Show the decision regions given by SVM
	Vec3b green(0,230,0), blue (230,0,0), gray(128, 128, 128);
	for(int i=0; i < image.rows; i++)
	{
		for(int j=0; j < image.cols; j++)
		{
			Mat sampleMat = (Mat_<float>(1,2) << i,j );
			float response = SVM.predict(sampleMat);
			if (response == 1)
				image.at<Vec3b>(j, i) = green;
			else if (response == -1)
				image.at<Vec3b>(j, i) = blue;
			else if (response == -2)
				image.at<Vec3b>(j, i) = gray;
		}
	}
	// Show the support vectors (white)
	int c = SVM.get_support_vector_count();
	for(int i=0; i < c; i++)
	{
		const float* v = SVM.get_support_vector(i);
		circle(image, Point((int)v[0],(int)v[1]), 6, Scalar(255, 255, 255), 2, 8);
	}
	
	// Show all the points (red)
	for(int i=0; i < NUM; i++)
		circle(image, Point((int)trainingData[i][0],(int)trainingData[i][1]),
				2, Scalar(0, 0, 255), 2, 0);
	
	imshow("linear SVM simple example", image);
	waitKey();
	return 0;
}
