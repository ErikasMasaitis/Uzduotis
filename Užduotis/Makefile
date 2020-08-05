CC=gcc
LD_LIBRARY=$(shell pwd)
FLAGS=-g -D_DEFAULT_SOURCE -Wall -Werror -pedantic
OBJ=main.c

Programs: libdynamic.so telt

telt: main.c
	$(CC) $(FLAGS) -o telt main.c -L$(LD_LIBRARY) -ldynamic -Wl,-rpath=$(LD_LIBRARY)

libdynamic.so: ./lib/dynamiclibrary.c ./lib/dynamiclibrary.h
	$(CC) -Wall -shared -fPIC -o libdynamic.so ./lib/dynamiclibrary.c

