CXX=g++
CXXFLAGS=-Wall -pedantic
LIBS=-lcrypt

all: proj5.x

proj5.x: proj5.o passserver.o
	$(CXX) $(CXXFLAGS) -o proj5.x proj5.o passserver.o $(LIBS)

proj5.o: proj5.cpp passserver.h
	$(CXX) $(CXXFLAGS) -c proj5.cpp

passserver.o: passserver.cpp passserver.h
	$(CXX) $(CXXFLAGS) -c passserver.cpp

clean:
	rm -f *.o *.x core.*
