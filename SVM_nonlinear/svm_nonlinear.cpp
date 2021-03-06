#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <ml.h>

#define	NTRAIN_SAMPLE    100 // Number of training samples per class
#define FRAC_LINEAR_SEP  0.9 // Fraction of samples which compose the linear separable part

using namespace cv;
using namespace std;

int main()
{
    const int WIDTH = 512, HEIGHT = 512;
    Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
    //------------------- <1> Set up training data randomly --------------------
    Mat labels   (2*NTRAIN_SAMPLE, 1, CV_32FC1);
    Mat trainData(2*NTRAIN_SAMPLE, 2, CV_32FC1);
    RNG rng(100); // Random value generation class
    
    // Set up the linearly separable part of the training data
    int nLinearSamples = (int) (FRAC_LINEAR_SEP * NTRAIN_SAMPLE);
    
    // Generate random points for the class 1
    Mat trainClass = trainData.rowRange(0, nLinearSamples);
    // The x coordinate of the points is in [0, 0.4)
    Mat c = trainClass.colRange(0 , 1);
    rng.fill(c, RNG::UNIFORM, Scalar(0*WIDTH), Scalar(0.4*WIDTH));
    // The y coordinate of the points is in [0, 1)
    c = trainClass.colRange(1 , 2);
    rng.fill(c, RNG::UNIFORM, Scalar(0*HEIGHT), Scalar(1.0*HEIGHT));
    
    // Generate random points for the class 2
    trainClass = trainData.rowRange(2*NTRAIN_SAMPLE-nLinearSamples, 2*NTRAIN_SAMPLE);
    // The x coordinate of the points is in [0.6, 1]
    c = trainClass.colRange(0 , 1);
    rng.fill(c, RNG::UNIFORM, Scalar(0.6*WIDTH), Scalar(1*WIDTH));
    // The y coordinate of the points is in [0, 1)
    c = trainClass.colRange(1 , 2);
    rng.fill(c, RNG::UNIFORM, Scalar(0.0*HEIGHT), Scalar(1*HEIGHT));
    
    //------- Set up the non-linearly separable part of the training data ------
    // Generate random points for the classes 1 and 2
    trainClass = trainData.rowRange(  nLinearSamples, 2*NTRAIN_SAMPLE-nLinearSamples);
    // The x coordinate of the points is in [0.4, 0.6)
    c = trainClass.colRange(0 , 1);
    rng.fill(c, RNG::UNIFORM, Scalar(0.4*WIDTH), Scalar(0.6*WIDTH));
    // The y coordinate of the points is in [0, 1)
    c = trainClass.colRange(1 , 2);
    rng.fill(c, RNG::UNIFORM, Scalar(0.0*HEIGHT), Scalar(1*HEIGHT));

    //------------------ Set up the labels for the classes ---------------------
    labels.rowRange(            0,   NTRAIN_SAMPLE).setTo(1); // Class 1
    labels.rowRange(NTRAIN_SAMPLE, 2*NTRAIN_SAMPLE).setTo(2); // Class 2
    
    //---------- <2> Set up the support vector machines parameters -------------
    CvSVMParams params;
    params.svm_type    = SVM::C_SVC;
    params.C 		   = 0.1;
    params.kernel_type = SVM::LINEAR;
    params.term_crit   = TermCriteria(CV_TERMCRIT_ITER, (int)1e7, 1e-6);

    //------------------------- <3> Train the svm ------------------------------
    CvSVM svm;
    svm.train(trainData, labels, Mat(), Mat(), params);
    
    //-------------------- <4> Show the decision regions -----------------------
    Vec3b green(0,100,0), blue (100,0,0);
    for (int i = 0; i < I.rows; ++i)
        for (int j = 0; j < I.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << i, j);
            float response = svm.predict(sampleMat);
            if      (response == 1)  I.at<Vec3b>(j, i) = green;
            else if (response == 2)  I.at<Vec3b>(j, i) = blue;
        }
    //-------------------- <5> Show the training data --------------------------
    int thick = -1, lineType = 8;
    float px, py;
    for (int i = 0; i < NTRAIN_SAMPLE; ++i) // Class 1, green
    {
        px = trainData.at<float>(i,0);
        py = trainData.at<float>(i,1);
        circle(I, Point((int)px, (int)py), 3, Scalar(0, 255, 0), thick, lineType);
    }
    for (int i = NTRAIN_SAMPLE; i <2*NTRAIN_SAMPLE; ++i) // Class 2, blue
    {
        px = trainData.at<float>(i,0);
        py = trainData.at<float>(i,1);
        circle(I, Point((int)px, (int)py), 3, Scalar(255, 0, 0), thick, lineType);
    }
    //------------------- <6> Show support vectors, gray -----------------------
    thick = 2, lineType = 8;
    for (int i = 0; i < svm.get_support_vector_count(); ++i)
    {
        const float* v = svm.get_support_vector(i);
        circle(I,  Point((int)v[0], (int)v[1]), 6, Scalar(128, 128, 128), thick, lineType);
    }
    
    imshow("SVM for Non-Linear Training Data", I);
    waitKey(0);
    return 0;
}

