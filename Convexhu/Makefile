CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: convexhull

convexhull.o: convexhull.cpp

convexhull: convexhull.o
	$(CC) $+ $(LIBS) -o $@

