/* Author: Oscar Rodriguez
 * Course: CMPS3350
 * Professor: Gordon
 * File Name: oscarR.cpp
 * 
 * 4 debugging steps
 * 1. identify/error report
 * 2. isolate/reproduce
 * 3. fix bug
 * 4. verify no new bugs
 * 
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

void showOscarCredits (int x, int y, GLuint id)
{ 
    Rect o;
	o.bot = 185;
	o.left = 150;
	o.center = 0;
	ggprint16(&o, 16, 0x0, "Oscar Rodriguez");	
	float wid = 100.0f;
        glColor3ub(255, 255, 255);
        glPushMatrix();
        glTranslatef((float)x, (float)y, 0);
        glBindTexture(GL_TEXTURE_2D, id);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid/2,  wid/2);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid/2, -wid/2);
        glEnd();
        glPopMatrix();
		

}

void spriteTest (int i) 	
{
    Image sprite[10] = {
		"chom/cs1.png",
		"chom/cs2.png",
		"chom/cs3.png",
		"chom/cs4.png",
		"chom/cs5.png",
		"chom/cs6.png",
		"chom/cs7.png",
		"chom/cs8.png",
		"chom/cs9.png",
		"chom/cs10.png"
	};
	
	GLuint chom;
	unsigned char *sData;
	int w = sprite[i].width;
	int h = sprite[i].height;
	int wid = 500.0f;
	glGenTextures(1, &chom);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(350, 350, 0);
    glBindTexture(GL_TEXTURE_2D, chom);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	sData = bAD(&sprite[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
			sData);
	free(sData);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid/2,  wid/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( wid/2, -wid/2);
    glEnd();
    glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}
