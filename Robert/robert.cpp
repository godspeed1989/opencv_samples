#include "robert.h"
#include "math.h"

void Robert( IplImage** src )
{
   if(!src || !*src)
   {
       exit(-1);
   }

   IplImage* dst = NULL;
   dst = cvCreateImage( cvGetSize(*src), (*src)->depth, (*src)->nChannels );
   if(!dst)
   {
       exit(-1);
   }
   cvSet( dst, cvScalarAll(255), 0 );

   int step = (*src)->widthStep;
   char* data = (*src)->imageData;
   for(int i = 0 ; i < (*src)->height ; i++ )
   {
      for(int j = 0 ; j < (*src)->width ; j++ )
      {
          #define white -1
          #define black 0
          bool pixel[9];
          /*
           *    4  5  7
           *    6  0  1
           *    8  2  3
           */
          pixel[0] = (data[step * (i) + j] == black)? 1 : 0;
          pixel[1] = (data[step * (i) + j+1] == black)? 1 : 0;
          pixel[2] = (data[step * (i + 1) + j] == black)? 1 : 0;
          pixel[3] = (data[step * (i + 1) + j+1] == black)? 1 : 0;
          pixel[4] = (data[step * (i - 1) + j-1] == black)? 1 : 0;
          pixel[5] = (data[step * (i - 1) + j] == black)? 1 : 0;
          pixel[6] = (data[step * (i) + j-1] == black)? 1 : 0;
          pixel[7] = (data[step * (i - 1) + j+1] == black)? 1 : 0;
          pixel[8] = (data[step * (i + 1) + j-1] == black)? 1 : 0;
          double result1 =
            sqrt( (pixel[0]-pixel[3])*(pixel[0]-pixel[3])+
                  (pixel[1]-pixel[2])*(pixel[1]-pixel[2]) );
          double result2 =
            sqrt( (pixel[0]-pixel[4])*(pixel[0]-pixel[4])+
                  (pixel[5]-pixel[6])*(pixel[5]-pixel[6]) );
          double result3 =
            sqrt( (pixel[0]-pixel[7])*(pixel[0]-pixel[7])+
                  (pixel[1]-pixel[5])*(pixel[1]-pixel[5]) );
          double result4 =
            sqrt( (pixel[0]-pixel[8])*(pixel[0]-pixel[8])+
                  (pixel[2]-pixel[6])*(pixel[2]-pixel[6]) );
          int result = ((result1+result2+result3+result4)/4.0 > 0.5)? 1 : 0;
          dst->imageData[step*i + j] = (result==1)? black : white;
      }//for
   }//for
   cvReleaseImage(src);
   *src = dst;
}

