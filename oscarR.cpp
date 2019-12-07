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

#include "oscarR.h"

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
		"images/chom/cs1.png",
		"images/chom/cs2.png",
		"images/chom/cs3.png",
		"images/chom/cs4.png",
		"images/chom/cs5.png",
		"images/chom/cs6.png",
		"images/chom/cs7.png",
		"images/chom/cs8.png",
		"images/chom/cs9.png",
		"images/chom/cs10.png"
	};
	
	GLuint chom;
	unsigned char *sData;
	int w = sprite[i].width;
	int h = sprite[i].height;
	int wid = 250.0f;
	glGenTextures(1, &chom);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(350, 200, 0);
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

void showTitle (int i) 	
{
    Image img[5] = {
		"images/title/kktitle.png",
		"images/title/kktitle1.png",
		"images/title/kktitle2.png",
		"images/title/kktitle3.png",
		"images/title/kktitle4.png",
	};
	
	GLuint texture;
	unsigned char *iData;
	int w = img[i].width;
	int h = img[i].height;
	int wid = 300.0f;
	int hid = 40.0f;
	glGenTextures(1, &texture);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(320, 400, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	iData = bAD(&img[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
			iData);
	free(iData);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -hid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid,  hid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid,  hid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( wid, -hid);
    glEnd();
    glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}
