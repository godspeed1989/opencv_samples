#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mshcd.hpp"

typedef struct Image
{
	u32 *data;
	u32 width, height;
	Image(): width(0), height(0)
	{
		data = NULL;
	}
	Image(u32 w, u32 h): width(w), height(h)
	{
		this->data = (u32*)malloc(w*h*sizeof(u32));
		assert(this->data);
	}
	Image(Image& image)
	{
		this->width = image.width;
		this->height = image.height;
		this->data = (u32*)malloc(image.width*image.height*sizeof(u32));
		assert(this->data);
		memcpy(this->data, image.data, image.width*image.height);
	}
	~Image()
	{
		if(data)
			free(data);
	}
	void init(u32 w, u32 h)
	{
		if(data)
			free(data);
		this->width = w;
		this->height = h;
		this->data = (u32*)malloc(w*h*sizeof(u32));
		assert(data);
	}
	u32 getWidth()
	{
		return this->width;
	}
	u32 getHeight()
	{
		return this->height;
	}
	u32& operator () (u32 x, u32 y)
	{
		assert(data);
		assert(x<width && y<height);
		return *(data+y*width+x);
	}
}Image;

#endif

