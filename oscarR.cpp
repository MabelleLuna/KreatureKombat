// Author: Oscar Rodriguez
// CMPS3350
// Professor: Gordon
//
//

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
void showOscarCredits ()
{ 
        Rect o;
	o.bot = 355;
	o.left = 150;
	o.center = 0;
	ggprint8b(&o, 16, 0x0, "Oscar Rodriguez");
}
