//this is my file
//i like files
//Author: Oscar Rodriguez

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
void oscarCredits ()
{
	Rect b;

	b.bot = 400;
	b.left = 150;
	b.center = 0; 
	ggprint8b(&b, 16, 0xFFFFFFFF, "Oscar Rodriguez");
}
