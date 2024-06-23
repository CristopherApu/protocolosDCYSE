all: nodo

nodo: nodo.o slip.o
	g++ -o nodo nodo.o slip.o

nodo.o: nodo.cpp slip.h ipv4.h
	g++ -c nodo.cpp

slip.o: slip.cpp slip.h
	g++ -c slip.cpp

clean:
	rm -f nodo nodo.o slip.o