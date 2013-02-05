CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: training

training.o: training.cpp
cvhaartraining.o: cvhaartraining.cpp
cvhaarclassifier.o: cvhaarclassifier.cpp
cvboost.o: cvboost.cpp
cvcommon.o: cvcommon.cpp
cvsamples.o: cvsamples.cpp

training: training.o cvhaartraining.o cvhaarclassifier.o \
			cvboost.o cvcommon.o cvsamples.o
	$(CC) $+ $(LIBS) -o $@

clean:
	rm -rf *.o

