//Logan's File
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

void showLoganCredits ()
{
	Rect l;
	l.bot = 250;
	l.left = 150;
	l.center = 0;
	ggprint8b(&l, 16, 0xFFFFFFFF, "Logan Lovett");
}
