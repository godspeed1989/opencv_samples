#ifndef __RECT_H__
#define __RECT_H__
#include <stdio.h>
#include "mshcd.hpp"
/**
 * A simple class describing a rectangle, along with a weight.
 */
typedef struct Rectangle
{
	u32 x, y;
	u32 width, height;
	double weight;
	Rectangle(): x(0), y(0), width(0), height(0), weight(0)
	{}
	Rectangle(u32 x, u32 y, u32 width, u32 height, double weight)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->weight = weight;
	}
	void print()
	{
		printf("{rect: %d %d %d %d %lf}\n", x, y, width, height, weight);
	}
}Rectangle;

#endif

