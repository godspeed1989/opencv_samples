CC=g++
LIBS=`pkg-config opencv --libs`
CPPFLAGS=`pkg-config opencv --cflags`

all: training createsamples

training.o: training.cpp
cvhaartraining.o: cvhaartraining.cpp
cvhaarclassifier.o: cvhaarclassifier.cpp
cvboost.o: cvboost.cpp
cvcommon.o: cvcommon.cpp
cvsamples.o: cvsamples.cpp
createsamples.o: createsamples.cpp

training: training.o cvhaartraining.o cvhaarclassifier.o cvboost.o cvcommon.o cvsamples.o
	$(CC) $+ $(LIBS) -o $@

createsamples: createsamples.o cvhaartraining.o cvhaarclassifier.o cvboost.o cvcommon.o cvsamples.o
	$(CC) $+ $(LIBS) -o $@

clean:
	rm -rf *.o
