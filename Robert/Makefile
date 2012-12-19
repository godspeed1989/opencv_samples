CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: robert

robert.o: robert.cpp
main.o: main.cpp

robert: main.o robert.o
	$(CC) $+ $(LIBS) -o $@

