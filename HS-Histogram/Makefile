CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: histogram

Histogram.o: Histogram.cpp

histogram: Histogram.o
	$(CC) $+ $(LIBS) -o $@

