/*
 * File:   loganL.h
 * Author: Logan Lovett
 */

#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "fonts.h"

class Character {
	private:
	int hp;
	std::string name;
	public:
	//Character(int hp, std::string name);
	void sethp(int hp_v);
	void setname(std::string name_v);
	int gethp() {return hp;}
	std::string getname() {return name;}
};
