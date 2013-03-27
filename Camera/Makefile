CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: clean camera

camera.o: camera.cpp
GetHaarCascade.o: GetHaarCascade.cpp

camera: camera.o GetHaarCascade.o
	$(CC) $+ $(LIBS) -o $@


clean:
	rm -rf *.o camera result.jpg

