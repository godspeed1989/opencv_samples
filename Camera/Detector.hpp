#ifndef __DETECTOR_H__
#define __DETECTOR_H__
#include <vector>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Stage.hpp"
#include "Point.hpp"
#include "CannyPruner.hpp"
#include "mshcd.hpp"
using namespace std;

u32 GetHaarCascade(const char* filename, vector<Stage>& Stages);

typedef struct Detector
{
	Point size;
	vector<Stage> stages;
	
	Detector(const char* filename)
	{
		size.x = size.y = GetHaarCascade(filename, stages);
		printf("Trained at %d x %d\n", size.x, size.y);
	}

	/**
	 * The algorithm tests, from sliding windows on the image, of variable size, 
	 * which regions should be considered as searched objects.
	 * @image The image file to scan.
	 * @baseScale The initial ratio between window size and the Haar classifier size.
	 * @scale_inc The scale increment of the window size, at each step.
	 * @increment The shift of the window at each sub-step, in terms of percentage of the window size.
	 * @min_neighbors The minimum number of rectangles needed to be kept in raw result.
	 * @return The found objects after merge.
	 */
	vector<Rectangle> getObjects(Image& image, double baseScale,
	                             double scale_inc, double increment,
	                             u32 min_neighbors, u8 canny_pruning)
	{
		vector<Rectangle> objects;
		u32 x, y, k;
		u32 width = image.getWidth();
		u32 height = image.getHeight();
		/* Compute the max scale of the detector, i.e. the size of the image divided by the size of the detector. */
		double maxScale = min((width+0.0f)/size.x, (height+0.0f)/size.y);
			
		//printf("Computing integral image and squared integral image.\n");
		Image integral(width, height);
		Image squares(width, height);
		for(x=0; x<width; x++)
		{
			u32 col = 0;
			u32 col2 = 0;
			for(y=0; y<height; y++)
			{
				u32 value = image(x, y);
				col += value;
				col2 += value*value;
				integral(x, y) = (x>0?integral(x-1,y):0) + col;
				squares(x, y) = (x>0?squares(x-1,y):0) + col2;
			}
		}
		/*for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
				printf("%d ", grayImage(i,j));
			printf("\n");
		}*/
		
		//printf("Start to detection...\n");
		CannyPruner pruner;
		if(canny_pruning)
		{
			//printf("Get integral canny to do canny prune.\n");
			pruner.getIntegralCanny(image);
		}
		double scale;
		for(scale=baseScale; scale<maxScale; scale*=scale_inc) // for each scale
		{
			u32 step = (u32) (scale * size.x * increment);
			u32 w = (scale * size.x);
			u32 h = (scale * size.y);
			//printf("*****Scale %lf step %d width %d height %d ", scale, step, w, h);
			/* For each position of the window on the image */
			for(x=0; x<width-w; x+=step)
			{
				for(y=0; y<height-h; y+=step)
				{
					if(canny_pruning)
					{
						u32 edges_density, d;
						Image& canny = pruner.canny;
						edges_density = canny(x+w,y+h)+canny(x,y)-canny(x,y+h)-canny(x+w,y);
						d = edges_density/(w*h);
						if( d<10 || d>100 )
							continue;
					}
					/* Perform each stage of the detector on the window */
					bool pass = true;
					for(k=0; k<stages.size(); k++)
					{
						/*If one stage fails, the zone is rejected.*/
						if(!stages[k].pass(integral, squares, x, y, scale))
						{
							pass = false;
							break;
						}
					}
					if(pass)
					{
						//printf("+");
						objects.push_back(Rectangle(x, y, w, h, 0));
					}
				}
			}
			//printf("\n");
		}
		/* The size of detected objects is in a increase sequence */
		//printf("Total found %d objects\n", objects.size());
		return merge(objects, min_neighbors);
	}
	
	/**
	 * Merge the raw detections resulting from the detection step 
	 * to avoid multiple detections of the same object.
	 * Two rectangles need to be merged if they overlap enough.
	 * @objs The raw detections returned by the detection algorithm.
	 * @min_neighbors The minimum number of rectangles needed to be kept.
	 * @return The merged rectangular detections.
	 */
	vector<Rectangle> merge(vector<Rectangle> objs, u32 min_neighbors)
	{
		vector<Rectangle> ret;
		u32 *mark = new u32[objs.size()];
		u32 nb_classes = 0;
		/* mark each rectangle with a class number */
		for(u32 i=0; i<objs.size(); i++)
		{
			bool found = false;
			for(u32 j=0; j<i; j++)
			{
				if(equals(objs[i], objs[j]))
				{
					found = true;
					mark[i] = mark[j];
				}
			}
			if(!found)
			{
				mark[i] = nb_classes;
				nb_classes++;
			}
		}
		u32 *neighbors = new u32[nb_classes];
		Rectangle *rects = new Rectangle[nb_classes];
		for(u32 i=0; i<nb_classes; i++)
		{
			neighbors[i] = 0;
			rects[i].x = rects[i].y = rects[i].width = rects[i].height = 0;
		}
		/* calculate number of rects of each class */
		for(u32 i=0; i<objs.size(); i++)
		{
			neighbors[mark[i]]++;
			rects[mark[i]].x += objs[i].x;
			rects[mark[i]].y += objs[i].y;
			rects[mark[i]].width += objs[i].width;
			rects[mark[i]].height += objs[i].height;
		}
		for(u32 i=0; i<nb_classes; i++)
		{
			u32 n = neighbors[i];
			if(n >= min_neighbors)
			{
				Rectangle r;
				r.x = (rects[i].x*2 + n)/(2*n);
				r.y = (rects[i].y*2 + n)/(2*n);
				r.width = (rects[i].width*2 + n)/(2*n);
				r.height = (rects[i].height*2 + n)/(2*n);
				ret.push_back(r);
			}
		}
		delete []mark;
		delete []neighbors;
		delete []rects;
		return ret;
	}
	
	/** Returns true if two rectangles overlap */
	bool equals(Rectangle& r1, Rectangle& r2)
	{
		u32 dist_x, dist_y;
		dist_x = (u32)(r1.width * 0.2);
		dist_y = (u32)(r1.height * 0.2);
		/* y - distance <= x <= y + distance */
		if(	r2.x <= r1.x + dist_x &&
			r2.x >= r1.x - dist_x &&
			r2.y <= r1.y + dist_y &&
			r2.y >= r1.y - dist_y &&
			(r2.width <= r1.width + dist_x || r2.width >= r1.width - dist_x) && 
			(r2.height <= r1.height + dist_y || r2.height >= r1.height - dist_y) )
			return true;
		if(	r1.x>=r2.x && r1.x+r1.width<=r2.x+r2.width &&
			r1.y>=r2.y && r1.y+r1.height<=r2.y+r2.height )
			return true;
		if(	r2.x>=r1.x && r2.x+r2.width<=r1.x+r1.width &&
			r2.y>=r1.y && r2.y+r2.height<=r1.y+r1.height )
			return true;
		return false;
	}
}Detector;

#endif

