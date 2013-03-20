CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: traincascade

boost.o: boost.cpp
features.o: features.cpp
traincascade.o: traincascade.cpp
cascadeclassifier.o: cascadeclassifier.cpp
haarfeatures.o: haarfeatures.cpp
lbpfeatures.o: lbpfeatures.cpp
HOGfeatures.o: HOGfeatures.cpp
imagestorage.o: imagestorage.cpp

traincascade: boost.o features.o cascadeclassifier.o traincascade.o haarfeatures.o lbpfeatures.o HOGfeatures.o imagestorage.o
	$(CC) $+ $(LIBS) -o $@

clean:
	rm -rf *.o
