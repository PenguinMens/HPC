.PHONY : dirs

COMMONFLAGS=-O3 -g#-DUSEPNG
INCLUDES=#-I/usr/include
LIBS=#-L/usr/lib64/ -lpng
NVFORTRAN_FLAGS=-module obj
CC=hipcc --offload-arch=gfx90a

all : dirs bin/game_of_life bin/game_of_life_hip

dirs :
	[ -d obj ] || mkdir obj
	[ -d bin ] || mkdir bin

clean :
	rm obj/*
	rm bin/*

obj/common.o : src/common.h src/common.c
	$(CC) $(COMMONFLAGS) $(INCLUDES) -o $@ -c src/common.c

obj/game_of_life.o : src/game_of_life.c
	$(CC) $(COMMONFLAGS) $(INCLUDES) -o $@ -c src/game_of_life.c

obj/game_of_life_hip.o : src/game_of_life_hip.cpp
	hipcc --offload-arch=gfx90a $(COMMONFLAGS) $(INCLUDES) -o $@ -c $^

bin/game_of_life : obj/game_of_life.o obj/common.o
	$(CC) $(COMMONFLAGS) $(INCLUDES) -o $@ obj/game_of_life.o obj/common.o $(LIBS)

bin/game_of_life_hip : obj/game_of_life_hip.o obj/common.o
	hipcc --offload-arch=gfx90a $(COMMONFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)