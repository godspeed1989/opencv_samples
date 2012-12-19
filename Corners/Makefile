
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: corners

corners.o: corners.c

corners: corners.o
	$(CC) $+ $(LIBS) -o $@

