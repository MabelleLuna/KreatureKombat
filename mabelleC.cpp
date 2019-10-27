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

#include "mabelleC.h"

void showMabelleCredits(int x, int y, GLuint id)
{
	Rect r;
	float wid = 100.0f;
	// Displays my name
	r.bot = 90;
	r.left = 152;
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


void drawSprite(GLuint texture, Image &sprite, 
float width, float height, float xpos, float ypos)
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	int ix = sprite.frame % sprite.columns;
	int iy = sprite.animation;
	float tx = (float) ix / sprite.columns;
	float ty = (float) iy / sprite.rows;
	float swidth = (float) 1.0 / sprite.columns;
	float sheight = (float) 1.0 / sprite.rows;
	
	if (sprite.frame >= sprite.columns) { iy = 1; }
	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(tx, ty + sheight);
	glVertex2i(xpos - width, ypos - height);
	glTexCoord2f(tx, ty);
	glVertex2i(xpos - width, ypos + height);
	glTexCoord2f(tx + swidth, ty);
	glVertex2i(xpos + width, ypos + height);
	glTexCoord2f(tx + swidth, ty + sheight);
	glVertex2i(xpos + width, ypos - height);
	glEnd();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
}
