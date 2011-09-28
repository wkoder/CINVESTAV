CXXFLAGS =	-O3 -g -Wall -fmessage-length=0
#CXXFLAGS = -g -Wall -fmessage-length=0
CXX = gcc $(CXXFLAGS)

LIBS =

suffixarray-moises:
	$(CXX) -o suffixarray-moises suffixarray.c $(LIBS)

all:	clean suffixarray-moises

clean:
	rm -f *.o suffixarray-moises
