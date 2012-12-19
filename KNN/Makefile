CC=g++
LIBS=`pkg-config opencv --libs`

CPPFLAGS=`pkg-config opencv --cflags`

all: KNN

KNN.o: KNN.cpp

KNN: KNN.o
	$(CC) $+ $(LIBS) -o $@

