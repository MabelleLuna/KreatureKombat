/* Mabelle Cruz
 * CS3350: Fall 2019
 * mabelleC.h
 */

#include <GL/glx.h>
#include "fonts.h"
#include "Image.h"

extern unsigned char *bAD(Image *img);
void drawPlayer1(int, int, int, int);
void drawPlayer2(int, int, int, int);
void drawSprite(GLuint, Image&, float, float, float, float);

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


