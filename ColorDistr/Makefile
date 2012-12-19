CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: colordist

ColorDist.o: ColorDist.cpp

colordist: ColorDist.o
	$(CC) $+ $(LIBS) -o $@

