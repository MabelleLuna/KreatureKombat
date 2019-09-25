/*
 * File:	loganL.cpp
 * Author:	Logan Lovett
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

void showLoganCredits (int x, int y, GLuint id)
{
	Rect l;
	l.bot = 370;
	l.left = 150;
	l.center = 0;
	ggprint8b(&l, 16, 0x0, "Logan Lovett");
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
