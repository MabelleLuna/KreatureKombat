//Author: 	 Brad Atkin
//Last Modified: 2019/09/17
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
//#include "ppm.h"
#include "fonts.h"

struct Vect {
	float x, y, z;
};

struct Shape {
	float width, height;
	float radius;
	Vect center;
};

class Box {
public:
	int xres, yres;
	Shape box;

} gB;

//void writeStoryText(string str);

void writeStoryText(const char* storyTextFileName) 
{
	const char* fileContent = storyTextFileName;

	Shape s1;
	glColor3ub(225,225,225);
	s1 = gB.box;
	glPushMatrix();

	s1.center.x = 300;
	s1.center.y = 100;
	//s1.center.y = 30;
	glTranslatef(s1.center.x, s1.center.y, s1.center.z);

	//s1->Vec = 50;
	int w = 200;
	int h = 50;
	glBegin(GL_QUADS);
		glVertex2i(-w, -h);
		glVertex2i(-w,  h);
		glVertex2i( w,  h);
		glVertex2i( w, -h);
	glEnd();
	glPopMatrix();

	unsigned int f = 0xFFFFFFFF;

	Rect b;

	b.bot =  100;
	b.left = 120;
	b.center = 0;
	ggprint8b(&b, 16, f, fileContent);

}

void showBradCredits ()
{
	Rect b;

	b.bot = 500;
	b.left = 150;
	b.center = 0;
	ggprint8b(&b, 16, 0xFFFFFFFF, "Brad Atkin");
}