$CC = gcc
#$FLAGS = -L/usr/local/include/SDL2 -lSDL2main -lSDL2 -lm

main: *.c
		${CC} main.c -o $@ -L/usr/local/include/SDL2 -lSDL2main -lSDL2 -lm
