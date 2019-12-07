//Author:			Brad Atkin
//Last Modified:	2019/10/15
//Filename:			bradA.cpp
//Description:		Contains functions written by Brad for the 
//					Kreature Kombat game

// 4 Steps of Debugging
// Identify, Isolate, Fix, Review

#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "bradA.h"
#include "Image.h"

using namespace std;

#define MAXBUTTONS 5

int nbuttons = 0;
int location = 0;
Button button[MAXBUTTONS];

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

struct Move {
	string name;
	int damage;
	float accuracy;
};

class Fighter {
public:
	string name;
	int strength;
	int health;
	struct MoveList {
		Move mvone;
		Move mvtwo;
		Move mvthree;
		Move mvfour;
	};
	void dealDamage(int n) {
		health = health - n;
	}
};

Move tackle = {
	"Tackle", 	//name
	2,			//damage
	.9,			//accuracy
};

Move scratch = {
	"Scratch",	//name
	2,			//damage
	.9,			//accuracy
};

Move bite = {
	"Bite",		//name
	4,			//damage
	.75,		//accuracy
};

Move rake = {
	"Rake",		//name
	6,			//damage
	.45,		//accuracy
};

Fighter yourDog = {
	"Puggish", 	//name
	2,			//strength
	10,			//health

};

void writeStoryText(const char* storyTextFileName, int storyIndex) 
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
	
	for(int i = 0; i < storyIndex; i++) {
		getline(file, str, '\n');
	}

	getline(file,str);
	file_contents = str;
	const char* fileContent = file_contents.c_str();
	ggprint8b(&b, 16, f, fileContent);
	
}

void showBradCredits(int x, int y, GLuint id)
{
	Rect b;

	b.bot = 400;
	b.left = 150;
	b.center = 0;
	//ggprint8b(&b, 16, 0x0, "Credits:");
	ggprint16(&b, 16, 0x0, "Brad Atkin");

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

void menuArrow(int x, int y, GLuint id) {
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

void bradShowScore()
{
	Rect b;

	b.bot =  400;
	b.left = 240;
	b.center = 0;

	ifstream file("scoresFile.txt");
	string str;
	string file_contents;

	while (getline(file, str)) {
		file_contents = str;
		file_contents.push_back('\n');
		const char* fileContent = file_contents.c_str();
		ggprint16(&b, 16, 0x00000000, fileContent);
	} 
}

// menu(): function to create the game menu
void menu()
{
	//glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
	Rect r;
	nbuttons=0;

	//size, position, & color
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 220;
	button[nbuttons].r.bot = 70;
	button[nbuttons].r.right =
		button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
		button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
		button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
		button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Play");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.0f;
	button[nbuttons].color[1] = 0.8f;
	button[nbuttons].color[2] = 0.1f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] / 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] / 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] / 0.5f;
	button[nbuttons].text_color = 0x36C6FF;
	nbuttons++;

	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 50;
	button[nbuttons].r.bot = 100;
	button[nbuttons].r.right =
		button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
		button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
		button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
		button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "How to play");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.0f;
	button[nbuttons].color[1] = 0.8f;
	button[nbuttons].color[2] = 0.1f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x36C6FF;
	nbuttons++;

	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 50;
	button[nbuttons].r.bot = 20;
	button[nbuttons].r.right =
		button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
		button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
		button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
		button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Scores");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.0f;
	button[nbuttons].color[1] = 0.8f;
	button[nbuttons].color[2] = 0.1f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x36C6FF;
	nbuttons++;
	
	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 400;
	button[nbuttons].r.bot = 100;
	button[nbuttons].r.right =
		button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
		button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
		button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
		button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Credits");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.0f;
	button[nbuttons].color[1] = 0.8f;
	button[nbuttons].color[2] = 0.9f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x36C6FF;
	nbuttons++;

	button[nbuttons].r.width = 140;
	button[nbuttons].r.height = 60;
	button[nbuttons].r.left = 400;
	button[nbuttons].r.bot = 20;
	button[nbuttons].r.right =
		button[nbuttons].r.left + button[nbuttons].r.width;
	button[nbuttons].r.top = button[nbuttons].r.bot +
		button[nbuttons].r.height;
	button[nbuttons].r.centerx = (button[nbuttons].r.left +
		button[nbuttons].r.right) / 2;
	button[nbuttons].r.centery = (button[nbuttons].r.bot +
		button[nbuttons].r.top) / 2;
	strcpy(button[nbuttons].text, "Quit");
	button[nbuttons].down = 0;
	button[nbuttons].click = 0;
	button[nbuttons].color[0] = 0.0f;
	button[nbuttons].color[1] = 0.8f;
	button[nbuttons].color[2] = 0.1f;
	button[nbuttons].dcolor[0] = button[nbuttons].color[0] * 0.5f;
	button[nbuttons].dcolor[1] = button[nbuttons].color[1] * 0.5f;
	button[nbuttons].dcolor[2] = button[nbuttons].color[2] * 0.5f;
	button[nbuttons].text_color = 0x36C6FF;
	nbuttons++;

	//draw the buttons
	for (int i=0; i< MAXBUTTONS; i++) {		
		glColor3f(1.0f, 1.0f, 0.0f);
			
		if (location == i) {
			glColor3fv(button[i].dcolor);
		} 
		else {
			glColor3fv(button[i].color);
		}
		
		glBegin(GL_QUADS);
			glVertex2i(button[i].r.left,  button[i].r.bot);
			glVertex2i(button[i].r.left,  button[i].r.top);
			glVertex2i(button[i].r.right, button[i].r.top);
			glVertex2i(button[i].r.right, button[i].r.bot);
		glEnd();

		r.left = button[i].r.centerx;
		r.bot  = button[i].r.centery-8;
		r.center = 1;
		
		ggprint16(&r, 16, button[i].text_color, button[i].text);

	}    
}

