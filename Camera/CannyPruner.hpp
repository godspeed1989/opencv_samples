#ifndef __CANNY_PRUNER_H__
#define __CANNY_PRUNER_H__
#include "Image.hpp"
#include "mshcd.hpp"

typedef struct CannyPruner
{
	Image canny;
	/**
	 * Compute the Canny Edge detector of an image.
	 * @grayImage The grayscale original image.
	 */
	void getIntegralCanny(Image& grayImage)
	{
		u32 i, j;
		u32 sum;
		canny.init(grayImage.width, grayImage.height);
		for(i=2; i<canny.width-2; i++)
		{
			for(j=2; j<canny.height-2; j++)
			{
				sum = 0;
				sum += 2  * grayImage(i-2, j-2);
				sum += 4  * grayImage(i-2, j-1);
				sum += 5  * grayImage(i-2, j+0);
				sum += 4  * grayImage(i-2, j+1);
				sum += 2  * grayImage(i-2, j+2);
				sum += 4  * grayImage(i-1, j-2);
				sum += 9  * grayImage(i-1, j-1);
				sum += 12 * grayImage(i-1, j+0);
				sum += 9  * grayImage(i-1, j+1);
				sum += 4  * grayImage(i-1, j+2);
				sum += 5  * grayImage(i+0, j-2);
				sum += 12 * grayImage(i+0, j-1);
				sum += 15 * grayImage(i+0, j+0);
				sum += 12 * grayImage(i+0, j+1);
				sum += 5  * grayImage(i+0, j+2);
				sum += 4  * grayImage(i+1, j-2);
				sum += 9  * grayImage(i+1, j-1);
				sum += 12 * grayImage(i+1, j+0);
				sum += 9  * grayImage(i+1, j+1);
				sum += 4  * grayImage(i+1, j+2);
				sum += 2  * grayImage(i+2, j-2);
				sum += 4  * grayImage(i+2, j-1);
				sum += 5  * grayImage(i+2, j+0);
				sum += 4  * grayImage(i+2, j+1);
				sum += 2  * grayImage(i+2, j+2);
				canny(i, j) = sum / 159;
			}
		}
		/*Computation of the discrete gradient of the image.*/
		Image grad(grayImage.width, grayImage.height);
		for(i=1; i<canny.width-1; i++)
		{
			for(j=1; j<canny.height-1; j++)
			{
				u32 grad_x, grad_y;
				grad_x =-canny(i-1,j-1)+canny(i+1,j-1)-2*canny(i-1,j)+2*canny(i+1,j)-canny(i-1,j+1)+canny(i+1,j+1);
				grad_y = canny(i-1,j-1)+2*canny(i,j-1)+canny(i+1,j-1)-canny(i-1,j+1)-2*canny(i,j+1)-canny(i+1,j+1);
				grad(i, j) = abs(grad_x) + abs(grad_y);
			}
		}
		/* Suppression of non-maxima of the gradient and computation of the integral Canny image. */
		for(i=0; i<canny.width; i++)
		{
			u32 col=0;
			for(j=0; j<canny.height; j++)
			{
				col += grad(i, j);
				canny(i, j) = (i>0?canny(i-1,j):0) + col;
			}
		}
	}
}CannyPruner;

#endif

