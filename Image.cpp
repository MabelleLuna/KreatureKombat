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


Image::Image(const char *fname, int row, int col) {
	file = fname;
	rows = row;
	columns = col;
	frameCounter = frame = animation = 0;
	if (fname[0] == '\0')
		return;
	int ppm_flag = 0;
	char name[40];
	strcpy(name, fname);
	int slen = strlen(name);
	char ppm[80];
	if (strncmp(name + (slen - 4), ".ppm", 4) == 0)
		ppm_flag = 1;
	if (ppm_flag) {
		strcpy(ppm, name);
	} else {
		name[slen - 4] = '\0';
		sprintf(ppm, "%s.ppm", name);
		char ts[100];
		sprintf(ts, "convert %s %s", fname, ppm);
		system(ts);
	}
	FILE *fpi = fopen (ppm, "r");
	if (fpi) {
		char line[200];
		fgets(line, 200, fpi);
		fgets(line, 200, fpi);
		while (line[0] == '#' || strlen(line) < 2)
			fgets(line, 200, fpi);
		sscanf(line, "%i %i", &width, &height);
		fgets(line, 200, fpi);
		int n = width * height * 3;			
		data = new unsigned char[n];			
		for (int i = 0; i < n; i++)
			data[i] = fgetc(fpi);
		fclose(fpi);
	} else {
		printf("ERROR opening image: %s\n",ppm);
		exit(0);
	}
	if (!ppm_flag)
		unlink(ppm);
}

Image::~Image() {
	delete [] data;
}
