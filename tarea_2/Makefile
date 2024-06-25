CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJS = nodo.o slip.o serial.o virtualSocket.o

all: nodo virtualSocket

nodo: nodo.o slip.o serial.o
	$(CXX) $(CXXFLAGS) -o nodo nodo.o slip.o serial.o

virtualSocket: virtualSocket.o
	$(CXX) $(CXXFLAGS) -o virtualSocket virtualSocket.o

nodo.o: nodo.cpp slip.h serial.h
	$(CXX) $(CXXFLAGS) -c nodo.cpp

slip.o: slip.cpp slip.h
	$(CXX) $(CXXFLAGS) -c slip.cpp

serial.o: serial.cpp serial.h
	$(CXX) $(CXXFLAGS) -c serial.cpp

virtualSocket.o: virtualSocket.cpp
	$(CXX) $(CXXFLAGS) -c virtualSocket.cpp

clean:
	rm -f nodo virtualSocket $(OBJS)