#include "cv.h"
#include "highgui.h"
#include <stdio.h>

#define ROW 10
#define COL 2
enum{RED , GREEN , BLUE , BLACK , YELLOW};

float Coordinates[ROW*COL] =
{
    0.1, 0.1,
    0.2, 0.2,
    0.3, 0.3,
    0.4, 0.4,
    3.1, 3.1,
    1.3, 2.7,
    2.0, 1.7,
    1.0, 2.0,
    0.5, 0.6,
    1.0, 0.9
};

CvMat* PCA(CvMat* Vector1);
void PrintMatrix(CvMat* Matrix, int color);
IplImage* Image;

int main()
{
    CvMat* Vector = cvCreateMat(ROW, COL, CV_32FC1);
    cvSetData(Vector , Coordinates, Vector->step);

    Image = cvCreateImage(cvSize(450, 450),8,3);
    cvSet(Image, cvScalarAll(255), NULL);
    Image->origin = 1;

    PCA(Vector);

    cvNamedWindow("Image" , 0);
    cvShowImage("Image" , Image);
    cvWaitKey(0);
    return 0;
}

CvMat* PCA(CvMat *Vector1)
{
    int col = Vector1->cols;
    CvMat* AvgVector;
    CvMat* EigenValue_Row;
    CvMat* EigenVector;

    AvgVector = cvCreateMat(1, col, CV_32FC1);
    EigenValue_Row = cvCreateMat(col, 1, CV_32FC1);
    EigenVector = cvCreateMat(col, col, CV_32FC1);

    //PrintMatrix(Vector1, RED);
    /* cvCalcPCA() */
    cvCalcPCA(Vector1,
              AvgVector,
              EigenValue_Row,
              EigenVector,
              CV_PCA_DATA_AS_ROW
              );
    PrintMatrix(AvgVector, BLUE);
    /* cvPorjectPCA() */
    cvProjectPCA(Vector1,
                 AvgVector,
                 EigenVector,
                 Vector1);
    PrintMatrix(Vector1, YELLOW);
    PrintMatrix(EigenVector, GREEN);
	/* cvBackProjectPCA */
    cvBackProjectPCA(Vector1,
                     AvgVector,
                     EigenVector,
                     Vector1);
    PrintMatrix(Vector1, BLACK); 
    
    cvReleaseMat(&AvgVector);
    cvReleaseMat(&EigenVector);
    cvReleaseMat(&EigenValue_Row);
    return Vector1;
}
//--------------------------------------------------------//
void PrintMatrix(CvMat *Matrix, int color)
{
	int i, j;
    CvScalar scalar;
    switch(color)
    {
        case RED:   scalar = CV_RGB(255, 0, 0); break;
        case GREEN: scalar = CV_RGB(0, 255, 0); break;
        case BLUE:  scalar = CV_RGB(0, 0, 255); break;
        case BLACK: scalar = CV_RGB(0, 0, 0);   break;
        case YELLOW:scalar = CV_RGB(255,255, 0);break;
        default:
            return;
    }

    for(i=0 ; i<Matrix->rows ; i++)
    {
        for(j=0 ; j<Matrix->cols ; j++)
        {
            cvCircle(Image,
              cvPoint((int)(cvGetReal2D(Matrix,i,0)*100),
                      (int)(cvGetReal2D(Matrix,i,1)*100)),
              0,//radius
              scalar,//color
              8,//thickness
              CV_AA,0);
        }//for
    }//for
}
