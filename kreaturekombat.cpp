//3350
//program: rainforest.cpp
//author:  Gordon Griesel
//Modified by the KreatureKombat Team
//date:    2019
//
//This program demonstrates the use of OpenGL and XWindows
//
//Texture maps are displayed.
//Press B to see bigfoot roaming his forest.
//
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
#include "bradA.h"


//defined types
typedef double Flt;
typedef double Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
			     (c)[1]=(a)[1]-(b)[1]; \
(c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define ALPHA 1

//-----------------------------------------------------------------------------
//Setup timers
//clock_gettime(CLOCK_REALTIME, &timePause);
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
unsigned int upause=0;
int titleF;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
		(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------

class Image {
	public:
		int width, height;
		unsigned char *data;
		~Image() { delete [] data; }
		Image(const char *fname) {
			if (fname[0] == '\0')
				return;
			//printf("fname **%s**\n", fname);
			int ppmFlag = 0;
			char name[40];
			strcpy(name, fname);
			int slen = strlen(name);
			char ppmname[80];
			if (strncmp(name+(slen-4), ".ppm", 4) == 0)
				ppmFlag = 1;
			if (ppmFlag) {
				strcpy(ppmname, name);
			} else {
				name[slen-4] = '\0';
				//printf("name **%s**\n", name);
				sprintf(ppmname,"%s.ppm", name);
				//printf("ppmname **%s**\n", ppmname);
				char ts[100];
				//system("convert eball.jpg eball.ppm");
				sprintf(ts, "convert %s %s", fname, ppmname);
				system(ts);
			}
			//sprintf(ts, "%s", name);
			FILE *fpi = fopen(ppmname, "r");
			if (fpi) {
				char line[200];
				fgets(line, 200, fpi);
				fgets(line, 200, fpi);
				//skip comments and blank lines
				while (line[0] == '#' || strlen(line) < 2)
					fgets(line, 200, fpi);
				sscanf(line, "%i %i", &width, &height);
				fgets(line, 200, fpi);
				//get pixel data
				int n = width * height * 3;			
				data = new unsigned char[n];			
				for (int i=0; i<n; i++)
					data[i] = fgetc(fpi);
				fclose(fpi);
			} else {
				printf("ERROR opening image: %s\n",ppmname);
				exit(0);
			}
			if (!ppmFlag)
				unlink(ppmname);
		}
};
Image img[10] = {
	"./images/bigfoot.png",
	"./images/streetbackground.png",
	"./images/forestTrans.png",
	"./images/umbrella.png",
	"./images/turtleResized.png",
	"./images/trash.png",
	"./images/cato.png",
	"./images/mabelleC.png",
	"./images/daytimestreet.png",
	"./images/right_arrow.png"
};

//const char* storyText = testTextFile.txt;

class Global {
	public:
		int done;
		int xres, yres;
		bool showCredits;
		bool showScores;
		bool writeStoryText;
		bool startGame;
		bool chooseCharacter;
		bool howTo;
		int storyIndex = 0;
		int arrowX = 30;
		int arrowY = 50;
		int menuOption = 1;
		GLuint textures[5];
		GLuint bigfootTexture;
		GLuint silhouetteTexture;
		GLuint backgroundTexture;
		GLuint background2Texture;
		GLuint forestTransTexture;
		GLuint umbrellaTexture;
		GLuint bradImgTexture;
		GLuint arrowTexture;
		GLuint trashTexture;
		GLuint catTexture;
		GLuint mabTexture;
		GLuint scoreTexture;
		int showBigfoot;
		int background;
		//int background2;
		int silhouette;
		int scores;
		int trees;
		int showRain;
		int showUmbrella;
		int deflection;
		Global() {
			logOpen();
			done=0;
			xres=800;
			yres=600;
			showBigfoot=0;
			background=1;
			//background2=1;
			scores=1;
			silhouette=1;
			trees=1;
			showRain=0;
			showUmbrella=0;
			deflection=0;
			showCredits = false;
			showScores = false;
			writeStoryText = false;
			startGame = false;
			chooseCharacter = false;
		}
		static Global *instance;
		static Global *getInstance(){
			if (!instance) {
				instance = new Global;
			}
			return instance;
		}

		~Global() {
			logClose();
		}
} g;
Global *Global::instance = 0;
Global *gl = gl->getInstance();

class Bigfoot {
	public:
		Vec pos;
		Vec vel;
} bigfoot;

class Raindrop {
	public:
		int type;
		int linewidth;
		int sound;
		Vec pos;
		Vec lastpos;
		Vec vel;
		Vec maxvel;
		Vec force;
		float length;
		float color[4];
		Raindrop *prev;
		Raindrop *next;
} *rainhead = NULL;
int ndrops=1;
int totrain=0;
int maxrain=0;
void deleteRain(Raindrop *node);
void cleanupRaindrops(void);
//
#define UMBRELLA_FLAT  0
#define UMBRELLA_ROUND 1
class Umbrella {
	public:
		int shape;
		Vec pos;
		Vec lastpos;
		float width;
		float width2;
		float radius;
} umbrella;

class X11_wrapper {
	private:
		Display *dpy;
		Window win;
	public:
		X11_wrapper() {
			GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
			//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
			XSetWindowAttributes swa;
			setupScreenRes(640, 480);
			dpy = XOpenDisplay(NULL);
			if (dpy == NULL) {
				printf("\n\tcannot connect to X server\n\n");
				exit(EXIT_FAILURE);
			}
			Window root = DefaultRootWindow(dpy);
			XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
			if (vi == NULL) {
				printf("\n\tno appropriate visual found\n\n");
				exit(EXIT_FAILURE);
			} 
			Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
			swa.colormap = cmap;
			swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
				StructureNotifyMask | SubstructureNotifyMask;
			win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
					vi->depth, InputOutput, vi->visual,
					CWColormap | CWEventMask, &swa);
			GLXContext glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
			glXMakeCurrent(dpy, win, glc);
			setTitle();
		}
		~X11_wrapper() {
			XDestroyWindow(dpy, win);
			XCloseDisplay(dpy);
		}
		void setTitle() {
			//Set the window title bar.
			XMapWindow(dpy, win);
			XStoreName(dpy, win, "Kreature Kombat");
		}
		void setupScreenRes(const int w, const int h) {
			g.xres = w;
			g.yres = h;
		}
		void reshapeWindow(int width, int height) {
			//window has been resized.
			setupScreenRes(width, height);
			//
			glViewport(0, 0, (GLint)width, (GLint)height);
			glMatrixMode(GL_PROJECTION); glLoadIdentity();
			glMatrixMode(GL_MODELVIEW); glLoadIdentity();
			glOrtho(0, g.xres, 0, g.yres, -1, 1);
			setTitle();
		}
		void checkResize(XEvent *e) {
			//The ConfigureNotify is sent by the
			//server if the window is resized.
			if (e->type != ConfigureNotify)
				return;
			XConfigureEvent xce = e->xconfigure;
			if (xce.width != g.xres || xce.height != g.yres) {
				//Window size did change.
				reshapeWindow(xce.width, xce.height);
			}
		}
		bool getXPending() {
			return XPending(dpy);
		}
		XEvent getXNextEvent() {
			XEvent e;
			XNextEvent(dpy, &e);
			return e;
		}
		void swapBuffers() {
			glXSwapBuffers(dpy, win);
		}
} x11;

//function prototypes
void initOpengl(void);
void checkMouse(XEvent *e);
int checkKeys(XEvent *e);
void init();
void physics(void);
void render(void);
void writeStoryText(const char*, int);
void showBradCredits(int, int, GLuint);
void showLoganCredits(int, int, GLuint);
void showOscarCredits(int, int, GLuint);
void drawCredits();
void showTitle(int);
void drawScores();
void drawEnemy(int, int, int, int); //(frame, wid, xpos, ypos)
void drawPlayer(int, int, int, int); //(frame, wid, xpos, ypos)
void gameScene();
void selectCharacter();
void displayHealth(int, int, int); // (hp, xpos, ypos)
extern void menu();
extern int nbuttons;
extern Button button[];
extern void chooseChar();

int main()
{
	initOpengl();
	init();
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	int done = 0;
	while (!done) {
		while (x11.getXPending()) {
			//XEvent e;
			//XNextEvent(dpy, &e);
			XEvent e = x11.getXNextEvent();
			x11.checkResize(&e);
			checkMouse(&e);
			done = checkKeys(&e);
		}
		//
		//Below is a process to apply physics at a consistent rate.
		//1. Get the current time.
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		//2. How long since we were here last?
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		//3. Save the current time as our new starting time.
		timeCopy(&timeStart, &timeCurrent);
		//4. Add time-span to our countdown amount.
		physicsCountdown += timeSpan;
		//5. Has countdown gone beyond our physics rate? 
		//       if yes,
		//           In a loop...
		//              Apply physics
		//              Reducing countdown by physics-rate.
		//              Break when countdown < physics-rate.
		//       if no,
		//           Apply no physics this frame.
		while (physicsCountdown >= physicsRate) {
			//6. Apply physics
			physics();
			//7. Reduce the countdown by our physics-rate
			physicsCountdown -= physicsRate;
		}
		//Always render every frame.
		render();
		x11.swapBuffers();
	}
	//cleanupXWindows();
	cleanup_fonts();
	return 0;
}

unsigned char *buildAlphaData(Image *img)
{
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//-----------------------------------------------
		//get largest color component...
		//*(ptr+3) = (unsigned char)((
		//		(int)*(ptr+0) +
		//		(int)*(ptr+1) +
		//		(int)*(ptr+2)) / 3);
		//d = a;
		//if (b >= a && b >= c) d = b;
		//if (c >= a && c >= b) d = c;
		//*(ptr+3) = d;
		//-----------------------------------------------
		//this code optimizes the commented code above.
		*(ptr+3) = (a|b|c);
		//-----------------------------------------------
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void initOpengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, g.xres, g.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	//
	//load the images file into a ppm structure.
	//
	//	bigfootImage     = ppm6GetImage("./images/bigfoot.ppm");
	//	forestImage      = ppm6GetImage("./images/forest.ppm");
	//	forestTransImage = ppm6GetImage("./images/forestTrans.ppm");
	//	umbrellaImage    = ppm6GetImage("./images/umbrella.ppm");
	//create opengl texture elements
	glGenTextures(1, &g.bigfootTexture);
	glGenTextures(1, &g.silhouetteTexture);
	glGenTextures(1, &g.backgroundTexture);
	glGenTextures(1, &g.background2Texture);
	glGenTextures(1, &g.umbrellaTexture);
	glGenTextures(1, &g.bradImgTexture);
	glGenTextures(1, &g.trashTexture);
	glGenTextures(1, &g.catTexture);
	glGenTextures(1, &g.mabTexture);
	glGenTextures(1, &g.scoreTexture);
	glGenTextures(1, &g.arrowTexture);
	//-------------------------------------------------------------------------
	//bigfoot
	//
	int w = img[0].width;
	int h = img[0].height;
	//
	glBindTexture(GL_TEXTURE_2D, g.bigfootTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[0].data);
	//-------------------------------------------------------------------------
	//Brad's img
	int w1 = img[4].width;
	int h2 = img[4].height;
	glBindTexture(GL_TEXTURE_2D, g.bradImgTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w1, h2, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[4].data);
	
	//menu arrow			
	int wA = img[9].width;
	int hA = img[9].height;
	glBindTexture(GL_TEXTURE_2D, g.arrowTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, wA, hA, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[9].data);
							
	//must build a new set of data...
	unsigned char *arrowSil = buildAlphaData(&img[9]);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wA, hA, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, arrowSil);
	free(arrowSil);

	//Logan's img
	int w2 = img[5].width;
	int h3 = img[5].height;
	glBindTexture(GL_TEXTURE_2D, g.trashTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w2, h3, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[5].data);	

	//Oscar's cat image
	int w6 = img[6].width;
	int h6 = img[6].height;
	glBindTexture(GL_TEXTURE_2D, g.catTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w6, h6, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[6].data);

	//Mabelle's Credits IMG
	int imgw = img[7].width;
	int imgh = img[7].height;
	glBindTexture(GL_TEXTURE_2D, g.mabTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgw, imgh, 0,
			GL_RGB, GL_UNSIGNED_BYTE, img[7].data);

	//silhouette
	//this is similar to a sprite graphic
	//
	glBindTexture(GL_TEXTURE_2D, g.silhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *silhouetteData = buildAlphaData(&img[0]);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//	GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//umbrella
	//
	glBindTexture(GL_TEXTURE_2D, g.umbrellaTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	silhouetteData = buildAlphaData(&img[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//	GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
	//
	//background
	glBindTexture(GL_TEXTURE_2D, g.backgroundTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			img[1].width, img[1].height,
			0, GL_RGB, GL_UNSIGNED_BYTE, img[1].data);
	//-------------------------------------------------------------------------

	glBindTexture(GL_TEXTURE_2D, g.background2Texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, img[8].width, img[8].height,
			0, GL_RGB, GL_UNSIGNED_BYTE, img[8].data);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, imgw, imgh, 0,
	//	GL_RGB, GL_UNSIGNED_BYTE, img[7].data);


	//forest transparent part
	//
	glBindTexture(GL_TEXTURE_2D, g.forestTransTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	w = img[2].width;
	h = img[2].height;
	unsigned char *ftData = buildAlphaData(&img[2]);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, ftData);
	free(ftData);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	//GL_RGB, GL_UNSIGNED_BYTE, bigfootImage->data);
	//-------------------------------------------------------------------------
}

void initSounds()
{

}

void init() {
	umbrella.pos[0] = 220.0;
	umbrella.pos[1] = (double)(g.yres-200);
	VecCopy(umbrella.pos, umbrella.lastpos);
	umbrella.width = 200.0;
	umbrella.width2 = umbrella.width * 0.5;
	umbrella.radius = (float)umbrella.width2;
	umbrella.shape = UMBRELLA_FLAT;
	MakeVector(-150.0,180.0,0.0, bigfoot.pos);
	MakeVector(6.0,0.0,0.0, bigfoot.vel);
}

void checkMouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down			
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
}

int checkKeys(XEvent *e)
{
	//keyboard input?
	int location = 0;
	static int shift=0;
	if (e->type != KeyPress && e->type != KeyRelease)
		return 0;
	int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
	if (e->type == KeyRelease) {
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	if (key == XK_Shift_L || key == XK_Shift_R) {
		shift=1;
		return 0;
	}
	switch (key) {
		case XK_b:
			g.showBigfoot ^= 1;
			if (g.showBigfoot) {
				bigfoot.pos[0] = -250.0;
			}
			break;
		case XK_c:
			g.showCredits ^= 1;
			drawCredits();
			break;
		case XK_s:
			g.showScores ^= 1;
			printf("scores: %i\n", g.scores);
			drawScores();
			break;
		case XK_d:
			g.deflection ^= 1;
			break;
		case XK_f:
			g.background ^= 1;
			break;
			/*case XK_s:
			  g.silhouette ^= 1;
			  printf("silhouette: %i\n", g.silhouette);
			  break;
			  */case XK_t:
			break;
		case XK_u:
			g.showUmbrella ^= 1;
			break;
		case XK_p:
			break;
		case XK_r:
			g.showRain ^= 1;
			break;
		case XK_a:
			g.startGame ^= 1;
			break;
		case XK_q:
			//writeStoryText("The story begins....");
			g.writeStoryText ^= 1;
			break;
		case XK_Return:
			if (g.writeStoryText == 1) {
				g.storyIndex += 1;
			}
			else {
				switch (g.menuOption) {
					case (1) :
						g.showScores ^= 1;
						break;
					case (2) :
						g.howTo ^= 1;
						break;
					case(3) :
						if (g.startGame == 1) {
							break;
						} else {
							g.startGame = 1;
						}
						break;
					case(4) :
						g.showCredits ^= 1;
						break;
					case(5) :
						return 1;
				}
			}
			break;
		case XK_Left:
			if (g.arrowX == 30 && g.arrowY == 50) {
				return 0;
				g.menuOption = 1;
			}
			if (g.arrowX == 30 && g.arrowY == 120) {
				g.arrowX = 30;
				g.arrowY = 50;
				g.menuOption = 1;
				return 0;
			} 
			if (g.arrowX == 210 && g.arrowY == 100) {
				g.arrowX = 30;
				g.arrowY = 120;
				g.menuOption = 2;
				return 0;
			}
			if (g.arrowX == 390 && g.arrowY == 120) {
				g.arrowX = 210;
				g.arrowY = 100;
				g.menuOption = 3;
				return 0;
			}
			if (g.arrowX == 390 && g.arrowY == 50) {
				g.arrowX = 390;
				g.arrowY = 120;
				g.menuOption = 4;
				return 0;
			}
			break;
		case XK_Right:
			if (g.arrowX == 30 && g.arrowY == 50) {
				g.arrowX = 30;
				g.arrowY = 120;
				g.menuOption = 2;
				return 0;
			}
			if (g.arrowX == 30 && g.arrowY == 120) {
				g.arrowX = 210;
				g.arrowY = 100;
				g.menuOption = 3;
				return 0;
			}
			if (g.arrowX == 210 && g.arrowY == 100) {
				g.arrowX = 390;
				g.arrowY = 120;
				g.menuOption = 4;
				return 0;
			}
			if (g.arrowX == 390 && g.arrowY == 120) {
				g.arrowX = 390;
				g.arrowY = 50;
				g.menuOption = 5;
				return 0;
			}
			break;
		case XK_Up:
			if (location == 0){
				location = 4;
			}
			else{
				location--;
			}
			break;
		case XK_Down:
			if (location == 4){
				location = 0;
			}
			else{
				location++;
			}
			break;
		case XK_equal:
			if (++ndrops > 40)
				ndrops=40;
			break;
		case XK_minus:
			if (--ndrops < 0)
				ndrops = 0;
			break;
		case XK_n:
			break;
		case XK_m:
			g.chooseCharacter ^= 1;
			break;
		case XK_w:
			if (shift) {
				//shrink the umbrella
				umbrella.width *= (1.0 / 1.05);
			} else {
				//enlarge the umbrella
				umbrella.width *= 1.05;
			}
			//half the width
			umbrella.width2 = umbrella.width * 0.5;
			umbrella.radius = (float)umbrella.width2;
			break;
		case XK_Escape:
			return 1;
			//break;
	}
	return 0;
}

Flt VecNormalize(Vec vec)
{
	Flt len, tlen;
	Flt xlen = vec[0];
	Flt ylen = vec[1];
	Flt zlen = vec[2];
	len = xlen*xlen + ylen*ylen + zlen*zlen;
	if (len == 0.0) {
		MakeVector(0.0,0.0,1.0,vec);
		return 1.0;
	}
	len = sqrt(len);
	tlen = 1.0 / len;
	vec[0] = xlen * tlen;
	vec[1] = ylen * tlen;
	vec[2] = zlen * tlen;
	return(len);
}


void physics()
{
	if (g.background) {
		titleF++;
		if (titleF == 5) titleF = 0;
	}
/*
	if (g.background2) {
		Rect r;
		unsigned int c = 0x00ffff44;
		r.bot = g.yres - 150;
		r.left = 10;
		r.center = 0;
		ggprint8b(&r, 16, c, "Start");

	}
*/	

}

void render()
{
	Rect r;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	if (g.background) {
		glBindTexture(GL_TEXTURE_2D, g.backgroundTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, g.yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(g.xres, g.yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(g.xres, 0);
		glEnd();
		showTitle(titleF);
	}
	unsigned int c = 0x00ffff44;
	r.bot = g.yres - 150;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, c, "B - Bigfoot");

	menu();
	menuArrow(g.arrowX,g.arrowY, g.arrowTexture);

	if (g.showCredits) {
		drawCredits();
	}
	if (g.showScores) {
		drawScores();
	}

	if (g.writeStoryText) {
		writeStoryText("kkstory.txt", g.storyIndex);
	}
	
	if (g.howTo) {
		showHowTo();
	}

	if (g.startGame){
		writeStoryText("kkstory.txt", g.storyIndex);
		gameScene();
	}

	if (g.chooseCharacter){
		selectCharacter();
	}
	
}

void gameScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	if (g.startGame){
		glBindTexture(GL_TEXTURE_2D, g.background2Texture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0, g.yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(g.xres, g.yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(g.xres, 0);
		glEnd();
		displayHealth(90, 90, 450);
		displayHealth(46, 550, 450);
		drawEnemy(0, 300, 530, 230);
		drawPlayer(0, 3, 90, 47);
	}
	
}

void selectCharacter()
{
	glClearColor(0.6, 0.8, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	Rect r;
	r.bot = gl->yres * 0.67f;
	r.left = gl->xres/2.5;
	ggprint16(&r, 16, 0x00000000, "Select Your Character");
	chooseChar();
	drawEnemy(0, 200, 530, 230);
}

void drawCredits()
{
	extern void showMabelleCredits(int, int, GLuint);
	glClear(GL_COLOR_BUFFER_BIT);
	Rect rcred;
	rcred.bot = gl->yres * 0.75f;
	rcred.left = gl->xres/2.8;
	rcred.center = 0;
	ggprint16(&rcred, 16, 0x0000ff00, "Credits");

	float offset = 0.18f;
	showMabelleCredits((gl->xres/2 - 300), gl->yres * (1 - offset), gl->textures[0]);

	showBradCredits(400,400, g.bradImgTexture);
	showLoganCredits(400,300,g.trashTexture);
	showOscarCredits(400,200,g.catTexture);
	showMabelleCredits(400,90,g.mabTexture);
}

void drawScores(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	extern void showScores(int, int, GLuint);
	void bradShowScore();
	glClear(GL_COLOR_BUFFER_BIT);
	Rect rcred;
	rcred.bot = gl->yres * 0.75f;
	rcred.left = gl->xres/2.8;
	rcred.center = 0;
	ggprint16(&rcred, 16, 0x0000ff00, "Scores");

	float offset = 0.18f;
	showScores((gl->xres/2 - 300), gl->yres * (1 - offset), gl->textures[0]);
	bradShowScore();
}
