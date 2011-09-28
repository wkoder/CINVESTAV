CXXFLAGS = -g -Wall
CXX = g++ $(CXXFLAGS)

OBJS = notes.o notes_test.o
LIBS = -fopenmp

notes.o:
	$(CXX) -c notes.c $(LIBS)

notes_test.o:
	$(CXX) -c notes_test.c $(LIBS)
	
notes: $(OBJS)
	$(CXX) -o notes_test $(OBJS) $(LIBS)

all: clean notes

clean:
	rm -f *.o notes
