
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: KMeans

KMeans.o: KMeans.c

KMeans: KMeans.o
	$(CC) $+ $(LIBS) -o $@

