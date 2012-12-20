#include <cv.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    //create a mat
    float matrix_data[]=
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    CvMat* Mat = cvCreateMat(4, 4, CV_32F);
    cvInitMatHeader(Mat, 4, 4, CV_32F, matrix_data, CV_AUTOSTEP);

    cvSave("data.xml", Mat, NULL, "My comment", cvAttrList(NULL, NULL));

    CvMat* Mat1 = (CvMat*)cvLoad("data.xml", NULL, NULL, NULL);
    if(!Mat1)
    {
        exit(-1);
    }

    float* data = Mat1->data.fl;
    int r, c, step = Mat1->cols;
    for(r=0 ; r<step ; r++)
    {
        for(c=0 ; c<step ; c++)
        {
            printf("%f\t", data[r*step + c]);
        }
        printf("\n");
    }

    cvReleaseMat(&Mat);
    cvReleaseMat(&Mat1);
    return 0;
}
