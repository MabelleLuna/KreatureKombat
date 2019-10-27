#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class Image {
	public:
		int width;
		int height;
		int rows;
		int columns;
		int frame;
		int frameCounter;
		int animation;
		unsigned char *data;
		const char *file;
		Image(const char* f, int r = 0, int c = 0);
		~Image();
};

