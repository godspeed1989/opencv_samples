CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: EqualizeHist

main.o: main.cpp
EqualizeHist.o: EqualizeHist.cpp

EqualizeHist: main.o EqualizeHist.o
	$(CC) $+ $(LIBS) -o $@

