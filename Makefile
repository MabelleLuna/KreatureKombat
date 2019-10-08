CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: rainforest

rainforest: rainforest.cpp log.cpp mabelleC.cpp bradA.cpp loganL.cpp oscarR.cpp
	g++ $(CFLAGS) rainforest.cpp log.cpp mabelleC.cpp bradA.cpp loganL.cpp oscarR.cpp libggfonts.a -Wall -Wextra  $(LFLAGS) -o rainforest

clean:
	rm -f rainforest
	rm -f *.o
