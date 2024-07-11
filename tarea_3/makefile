CXX = g++
CXXFLAGS = -Wall -g -std=c++11

TARGET = nodo
VIRTUAL_SOCKET = src/virtualSocket
VIRTUAL_SOCKET_SRC = src/virtualSocket.cpp
SRCS = src/nodo.cpp src/funciones.cpp

all: nodo virtualSocket

nodo: $(SRCS)
	$(CXX) $(CXXFLAGS) -o nodo $(SRCS)

virtualSocket: $(VIRTUAL_SOCKET_SRC)
	$(CXX) $(CXXFLAGS) -o $(VIRTUAL_SOCKET) $(VIRTUAL_SOCKET_SRC)

clean:
	rm -f nodo $(VIRTUAL_SOCKET)
	rm -rf tmp

prepara_carpeta:
	rm -rf /tmp/p1 /tmp/p2 /tmp/p3 /tmp/p4 /tmp/p5 /tmp/p6 /tmp/p7 /tmp/p8 /tmp/p9 /tmp/p10

run_socket: prepara_carpeta
	socat -d -d pty,raw,echo=0,link=/tmp/p1 pty,raw,echo=0,link=/tmp/p2 &
	socat -d -d pty,raw,echo=0,link=/tmp/p3 pty,raw,echo=0,link=/tmp/p4 &
	socat -d -d pty,raw,echo=0,link=/tmp/p5 pty,raw,echo=0,link=/tmp/p6 &
	socat -d -d pty,raw,echo=0,link=/tmp/p7 pty,raw,echo=0,link=/tmp/p8 &
	socat -d -d pty,raw,echo=0,link=/tmp/p9 pty,raw,echo=0,link=/tmp/p10 &

nodo1: nodo
	./nodo 192.168.130.1 /tmp/p1 /tmp/p2

nodo2: nodo
	./nodo 192.168.130.2 /tmp/p3 /tmp/p4

nodo3: nodo
	./nodo 192.168.130.3 /tmp/p5 /tmp/p6

nodo4: nodo
	./nodo 192.168.130.4 /tmp/p7 /tmp/p8

nodo5: nodo
	./nodo 192.168.130.5 /tmp/p9 /tmp/p10