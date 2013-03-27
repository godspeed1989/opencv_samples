#ifndef __POINT_H__
#define __POINT_H__
#include "mshcd.hpp"

typedef struct Point
{
	u32 x;
	u32 y;
	Point(u32 _x=0, u32 _y=0): x(_x), y(_y) {}
}Point;

#endif

