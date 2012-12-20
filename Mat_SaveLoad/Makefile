
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: Mat

Mat.o: Mat.c

Mat: Mat.o
	$(CC) $+ $(LIBS) -o $@

