CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		fletcherreevesmain.o fletcherreeves.o

LIBS =

TARGET =	fletcherreevesmain

fletcherreeves.o:
	$(CXX) -c fletcherreeves.cpp $(LIBS)

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	clean $(TARGET)

clean:
	rm -f *.o $(OBJS) $(TARGET)
