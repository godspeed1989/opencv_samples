CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: houghCircle

HoughCircle.o: HoughCircle.cpp

houghCircle: HoughCircle.o
	$(CC) $+ $(LIBS) -o $@

