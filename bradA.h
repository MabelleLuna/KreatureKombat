#ifndef bradA_h
#define bradA_h

#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"
#include <fstream>
#include <string>

typedef struct t_button {
	Rect r;
	char text[32];
	int over;
	int down;
	int click;
	float color[3];
	float dcolor[3];
	unsigned int text_color;
} Button;

void menu();
extern int location;
void menuArrow(int x, int y, GLuint id);


/*

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
*/
#endif