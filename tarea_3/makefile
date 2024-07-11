CC=g++
CFLAGS=-Wall
SRC_DIR=src

all: nodo virtualSocket

nodo: $(SRC_DIR)/nodo.o $(SRC_DIR)/funciones.o $(SRC_DIR)/serial.o $(SRC_DIR)/slip.o $(SRC_DIR)/ipv4.o
	$(CC) $(CFLAGS) -o nodo $(SRC_DIR)/nodo.o $(SRC_DIR)/funciones.o $(SRC_DIR)/serial.o $(SRC_DIR)/slip.o $(SRC_DIR)/ipv4.o

$(SRC_DIR)/nodo.o: $(SRC_DIR)/nodo.cpp $(SRC_DIR)/nodo.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/nodo.cpp -o $(SRC_DIR)/nodo.o

$(SRC_DIR)/funciones.o: $(SRC_DIR)/funciones.cpp $(SRC_DIR)/nodo.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/funciones.cpp -o $(SRC_DIR)/funciones.o

$(SRC_DIR)/serial.o: $(SRC_DIR)/serial.cpp $(SRC_DIR)/serial.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/serial.cpp -o $(SRC_DIR)/serial.o

$(SRC_DIR)/slip.o: $(SRC_DIR)/slip.cpp $(SRC_DIR)/slip.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/slip.cpp -o $(SRC_DIR)/slip.o

$(SRC_DIR)/ipv4.o: $(SRC_DIR)/ipv4.cpp $(SRC_DIR)/ipv4.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ipv4.cpp -o $(SRC_DIR)/ipv4.o

virtualSocket: $(SRC_DIR)/virtualSocket.cpp
	$(CC) $(CFLAGS) -o virtualSocket $(SRC_DIR)/virtualSocket.cpp

clean:
	rm -f nodo virtualSocket $(SRC_DIR)/*.o
	rm -f /tmp/p*

reboot: clean all
	mkdir -p /tmp
	socat -d -d pty,raw,echo=0,link=/tmp/p1 pty,raw,echo=0,link=/tmp/p2 &
	socat -d -d pty,raw,echo=0,link=/tmp/p3 pty,raw,echo=0,link=/tmp/p4 &
	socat -d -d pty,raw,echo=0,link=/tmp/p5 pty,raw,echo=0,link=/tmp/p6 &
	socat -d -d pty,raw,echo=0,link=/tmp/p7 pty,raw,echo=0,link=/tmp/p8 &
	socat -d -d pty,raw,echo=0,link=/tmp/p9 pty,raw,echo=0,link=/tmp/p10 &
	sleep 5 # Esperar a que los puertos se configuren
	./nodo 192.168.1.1 /tmp/p1 /tmp/p2