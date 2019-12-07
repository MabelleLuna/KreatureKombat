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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid/2,  wid/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( wid/2, -wid/2);
    glEnd();
    glPopMatrix();
}

void drawEnemy (int i, int wid, int xpos, int ypos) 	
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
	
	GLuint texture;
	unsigned char *sData;
	int w = sprite[i].width;
	int h = sprite[i].height;
	//int wid = 200.0f;
	glGenTextures(1, &texture);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(xpos, ypos, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	sData = bAD(&sprite[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, sData);
	free(sData);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2i( wid/2,  wid/2);
    glTexCoord2f(0.0f, 1.0f); glVertex2i( wid/2, -wid/2);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, iData);
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

void displayHealth (int i, int xpos, int ypos) 	
{

    if (i > 90) i = 10;
	else if (i > 80) i = 9;
	else if (i > 70) i = 8;
	else if (i > 60) i = 7;
	else if (i > 50) i = 6;
	else if (i > 40) i = 5;
	else if (i > 30) i = 4;
	else if (i > 20) i = 3;
	else if (i > 10) i = 2;
	else if (i > 0) i = 1;
	else i = 0;
	
	Image img[11] = {
		"images/hBar/hbar0.png",
		"images/hBar/hbar1.png",
		"images/hBar/hbar2.png",
		"images/hBar/hbar3.png",
		"images/hBar/hbar4.png",
		"images/hBar/hbar5.png",
		"images/hBar/hbar6.png",
		"images/hBar/hbar7.png",
		"images/hBar/hbar8.png",
		"images/hBar/hbar9.png",
		"images/hBar/hbar10.png"
	};
	
	GLuint texture;
	unsigned char *iData;
	int w = img[i].width;
	int h = img[i].height;
	int wid = 100.0f;
	int hid = 44.0f;
	glGenTextures(1, &texture);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(xpos, ypos, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	iData = bAD(&img[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, iData);
	free(iData);
    glBegin(GL_QUADS);
	if (xpos < 200) {
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -hid);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid,  hid);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( wid,  hid);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( wid, -hid);
	} else {
		glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid, -hid);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid,  hid);
		glTexCoord2f(0.0f, 0.0f); glVertex2i( wid,  hid);
		glTexCoord2f(0.0f, 1.0f); glVertex2i( wid, -hid);
	}
    glEnd();
    glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}

void drawPlayer (int i, int choice, int xpos, int ypos) 	
{
	Image img[3] = {
		"player/d1.png",
		"player/d2.png",
		"player/d3.png"
	};
	
	if (choice == 2) {
		
		Image img[3] = {
			"player/c1.png",
			"player/c2.png",
			"player/c3.png"
		};
		
	} else if (choice == 3) {
		
		Image img[4] = {
			"player/p.png",
			"player/p1.png",
			"player/p2.png",
			"player/p3.png"
		};
	}
	
	
	GLuint texture;
	unsigned char *iData;
	int w = img[i].width;
	int h = img[i].height;
	int wid = 300.0f;
	glGenTextures(1, &texture);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_ALPHA_TEST);
	glPushMatrix();
    glTranslatef(xpos, ypos, 0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	iData = bAD(&img[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
		GL_UNSIGNED_BYTE, iData);
	free(iData);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
    glTexCoord2f(1.0f, 0.0f); glVertex2i( wid/2,  wid/2);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( wid/2, -wid/2);
    glEnd();
    glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}