CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: face_det

face_det.o: face_det.cpp

face_det: face_det.o
	$(CC) $+ $(LIBS) -o $@

clean:
	rm -rf face_det.o

