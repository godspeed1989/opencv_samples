CC=gcc
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: pca

PCA.o: PCA.c

pca: PCA.o
	$(CC) $(CFLAGS) $+ $(LIBS) -o $@

