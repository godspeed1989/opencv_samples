#include "EqualizeHist.h"

void EqualizeHist(IplImage** imgSrc)
{
	int i;
	IplImage *pImageChannel[4] = { 0, 0, 0, 0 };
	IplImage *pImage = cvCreateImage(cvGetSize((*imgSrc)), (*imgSrc)->depth, (*imgSrc)->nChannels);

	for( i = 0; i < (*imgSrc)->nChannels; i++ )
	{
		pImageChannel[i] = cvCreateImage( cvGetSize((*imgSrc)), (*imgSrc)->depth, 1 );
	}

	cvSplit( (*imgSrc), pImageChannel[0], pImageChannel[1],
						pImageChannel[2], pImageChannel[3] );

	for( i = 0; i < pImage->nChannels; i++ )
	{
		cvEqualizeHist( pImageChannel[i], pImageChannel[i] );
	}

	cvMerge( pImageChannel[0], pImageChannel[1],
			 pImageChannel[2], pImageChannel[3], pImage );

	cvReleaseImage(imgSrc);
	(*imgSrc) = pImage;
}

