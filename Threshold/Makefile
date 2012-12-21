
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: threshold

Threshold.o: Threshold.c

threshold: Threshold.o
	$(CC) $+ $(LIBS) -o $@

