CFLAGS = -I ./include
##LIB    = ./lib/fmod/libfmodex64.so
LFLAGS = -lrt -lX11 -lGLU -lGL -lm #-lXrandr

all: rainforest readScores

rainforest: rainforest.cpp log.cpp mabelleC.cpp bradA.cpp loganL.cpp oscarR.cpp Image.cpp
	g++ $(CFLAGS) rainforest.cpp log.cpp mabelleC.cpp bradA.cpp loganL.cpp oscarR.cpp Image.cpp libggfonts.a -Wall -Wextra  $(LFLAGS) -o rainforest

readScores: readScores.cpp
	g++ readScores.cpp -Wall -oreadScores -lssl -lcrypto

clean:
	rm -f rainforest
	rm -f readScores
	rm -f *.o
