//Author:			Brad Atkin
//Last Modified:	2019/09/26
//Filename:			bradA.cpp
//Description:		Contains functions written by Brad for the Kreature Kombat game

#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <fstream>
#include <string>

using namespace std;


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

	//const char* fileContent = storyTextFileName;

	ifstream file(storyTextFileName);
	string str;
	string file_contents;
	
	
	while (getline(file, str)) {
		file_contents = str;
		file_contents.push_back('\n');
		const char* fileContent = file_contents.c_str();
		ggprint8b(&b, 16, f, fileContent);
	} 



}

void showBradCredits(int x, int y, GLuint id)
{
	Rect b;

	b.bot = 400;
	b.left = 150;
	b.center = 0;
	ggprint8b(&b, 16, 0x0, "Credits:");
	ggprint8b(&b, 16, 0x0, "Brad Atkin");

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