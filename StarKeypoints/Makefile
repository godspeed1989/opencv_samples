CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: star

star.o: star.cpp

star: star.o
	$(CC) $+ $(LIBS) -o $@

