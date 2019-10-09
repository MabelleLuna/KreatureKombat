/* mabelleC.cpp
 *
 * Mabelle Cruz
 * CS335: Fall 2019
 *
 *
 * List 4 steps of debugging:
 * 1. Identify and discover the bug and why it happened
 * 2. Isolate and seperate the healthy code from the problem
 * 3. Fix the bug by making a unit test
 * 4  Review your code and make sure it works
 *
 */

#include <GL/glx.h>
#include "fonts.h"

void showMabelleCredits(int x, int y, GLuint id)
{
	Rect r;
	float wid = 100.0f;
	// Displays my name
	r.bot = 90;
	r.left = 90;
	r.center = 0;
	ggprint16(&r, 16, 0x0, "Mabelle Cruz");
	// Displays my picture
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

void showScores(int x, int y, GLuint id)
{
	Rect r;
	float wid = 100.0f;
	r.bot = 200;
	r.left = 200;
	r.center = 0;
	ggprint16(&r, 16, 0x0, " ");
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

