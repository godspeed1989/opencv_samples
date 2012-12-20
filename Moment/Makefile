
LIBS=`pkg-config opencv --libs`
CFLAGS=`pkg-config opencv --cflags`

all: moment

moment.o: moment.c

moment: moment.o
	$(CC) $(CFLAGS) $+ $(LIBS) -o $@

