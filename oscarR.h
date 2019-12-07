/*
 * File:   oscarR.h
 * Author: Oscar Rodriguez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include "Image.h"

// Required to make transparency work
unsigned char *bAD(Image *img)
{
	int i;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	unsigned char a, b, c;
	unsigned char t0 = *(data + 0);
	unsigned char t1 = *(data + 1);
	unsigned char t2 = *(data + 2);
	for (i = 0; i < img->width * img->height * 3; i += 3)
	{
			a = *(data + 0);
			b = *(data + 1);
			c = *(data + 2);
			*(ptr + 0) = a;
			*(ptr + 1) = b;
			*(ptr + 2) = c;
			*(ptr + 3) = 1;
			if (a == t0 && b == t1 && c == t2)
					*(ptr + 3) = 0;
			ptr += 4;
			data += 3;
	}
	return newdata;
}
