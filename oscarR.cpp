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
    Image sprite[5] = {
		"chom/cs1.png",
		"chom/cs2.png",
		"chom/cs3.png",
		"chom/cs4.png",
		"chom/cs5.png"};
	
		GLuint chom;
		//for (int i = 0; i<5; i++) {
		int w = sprite[i].width;
		int h = sprite[i].height;
		int wid = 100.0f;
		glColor3ub(255, 255, 255);
		glGenTextures(1, &chom);
		glPushMatrix();
        glTranslatef(350, 350, 0);
        glBindTexture(GL_TEXTURE_2D, chom);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
				sprite[i].data);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid/2, -wid/2);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid/2,  wid/2);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid/2,  wid/2);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid/2, -wid/2);
        glEnd();
        glPopMatrix();
	//  }
}
