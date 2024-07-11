CC=g++
CFLAGS=-Wall

all: nodo virtualSocket

nodo: src/nodo.o src/funciones.o src/serial.o src/slip.o src/ipv4.o
	$(CC) $(CFLAGS) -o nodo src/nodo.o src/funciones.o src/serial.o src/slip.o src/ipv4.o

virtualSocket: src/virtualSocket.cpp
	$(CC) $(CFLAGS) -o virtualSocket src/virtualSocket.cpp

src/nodo.o: src/nodo.cpp src/nodo.h src/funciones.h
	$(CC) $(CFLAGS) -c src/nodo.cpp -o src/nodo.o

src/funciones.o: src/funciones.cpp src/nodo.h src/funciones.h
	$(CC) $(CFLAGS) -c src/funciones.cpp -o src/funciones.o

src/serial.o: src/serial.cpp src/serial.h
	$(CC) $(CFLAGS) -c src/serial.cpp -o src/serial.o

src/slip.o: src/slip.cpp src/slip.h
	$(CC) $(CFLAGS) -c src/slip.cpp -o src/slip.o

src/ipv4.o: src/ipv4.cpp src/ipv4.h
	$(CC) $(CFLAGS) -c src/ipv4.cpp -o src/ipv4.o

clean:
	rm -f nodo virtualSocket src/*.o /tmp/p*

reboot: clean all
	socat -d -d pty,raw,echo=0,link=/tmp/p1 pty,raw,echo=0,link=/tmp/p2 &
	socat -d -d pty,raw,echo=0,link=/tmp/p3 pty,raw,echo=0,link=/tmp/p4 &
	socat -d -d pty,raw,echo=0,link=/tmp/p5 pty,raw,echo=0,link=/tmp/p6 &
	socat -d -d pty,raw,echo=0,link=/tmp/p7 pty,raw,echo=0,link=/tmp/p8 &
	socat -d -d pty,raw,echo=0,link=/tmp/p9 pty,raw,echo=0,link=/tmp/p10 &

nodo_a: all
	./nodo 192.168.1.1 /tmp/p1 /tmp/p2

nodo_b: all
	./nodo 192.168.1.2 /tmp/p3 /tmp/p4

nodo_c: all
	./nodo 192.168.1.3 /tmp/p5 /tmp/p6

nodo_d: all
	./nodo 192.168.1.4 /tmp/p7 /tmp/p8

nodo_e: all
	./nodo 192.168.1.5 /tmp/p9 /tmp/p10