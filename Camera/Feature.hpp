#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <vector>
#include <math.h>
#include "Rectangle.hpp"
#include "Point.hpp"
#include "Image.hpp"
#include "mshcd.hpp"
using namespace std;
/** 
 * A feature is located at a node of a tree
 * Returns LEFT or RIGHT depending on the computed value and a threshold.
 */
#define LEFT   0
#define RIGHT  1
typedef struct Feature
{
	Rectangle rects[3];
	u32 nb_rects;
	double threshold;
	double left_val, right_val;
	bool has_left_val, has_right_val;
	u32 left_node, right_node;
	u32 width, height;
	u32 tilted;
	
	Feature()
	{
		width = height = nb_rects = 0;
		left_node = right_node = 0;
		has_left_val = has_right_val = false;
	}
	Feature(double threshold,
			double left_val, u32 left_node, bool has_left_val,
			double right_val, u32 right_node, bool has_right_val)
	{
		width = height = nb_rects = 0;
		this->threshold = threshold;
		this->left_val = left_val;
		this->left_node = left_node;
		this->has_left_val = has_left_val;
		this->right_val = right_val;
		this->right_node = right_node;
		this->has_right_val = has_right_val;
	}

	u32 getLeftOrRight(Image& integral, Image& squares,
						u32 x, u32 y, double scale)
	{
		/* Compute the area of the window.*/
		u32 w = width * scale;
		u32 h = height * scale;
		double inv_area = 1.0/(w*h);
		
		/* Compute the sum of the pixel values in the window, 
		 * get the mean and variance of pixel values */
		u32 total_x = integral(x+w,y+h)+integral(x,y)-integral(x+w,y)-integral(x,y+h);
		u32 total_x2 = squares(x+w,y+h)+squares(x,y)-squares(x+w,y)-squares(x,y+h);
		
		double moy = total_x * inv_area;
		double vnorm = total_x2 * inv_area - moy * moy;
		vnorm = (vnorm > 1.0) ? sqrt(vnorm) : 1.0;

		double rect_sum = 0;
		/* For each rectangle in the feature. */
		for(u32 k=0; k<nb_rects; k++)
		{
			Rectangle& rect = this->rects[k];
			/* Scale the rectangle according to the window size. */
			u32 rx1 = x + (u32) (scale * rect.x);
			u32 rx2 = x + (u32) (scale * (rect.x+rect.width));
			u32 ry1 = y + (u32) (scale * rect.y);
			u32 ry2 = y + (u32) (scale * (rect.y+rect.height));
			rect_sum += (integral(rx2,ry2)+integral(rx1,ry1)-integral(rx1,ry2)-integral(rx2,ry1))*rect.weight;
		}
		double rect_sum2 = rect_sum * inv_area;
		/* Return LEFT or RIGHT depending on how the total sum compares to the threshold. */
		return (rect_sum2 < threshold*vnorm) ? LEFT : RIGHT;
	}

	void addRect(Rectangle& r)
	{
		this->rects[nb_rects++] = r;
		assert(nb_rects<=3);
	}
	
	void print()
	{
		rects[0].print();
		rects[1].print();
		rects[2].print();
		printf("{L: %lf %d %d}\n", left_val, has_left_val, left_node);
		printf("{R: %lf %d %d}\n", right_val, has_right_val, right_node);
	}
}Feature;

#endif

