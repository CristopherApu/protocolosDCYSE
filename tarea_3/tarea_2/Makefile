# Compila todos los archivos
all: nodo virtualSocket

nodo: serial.o slip.o ipv4.o nodo.o
	g++ -Wall slip.o serial.o ipv4.o nodo.o -o nodo

virtualSocket: virtualSocket.o
	g++ -Wall virtualSocket.o -o virtualSocket

serial.o: serial.cpp
	g++ -Wall -c serial.cpp

slip.o: slip.cpp
	g++ -Wall -c slip.cpp

ipv4.o: ipv4.cpp
	g++ -Wall -c ipv4.cpp

nodo.o: nodo.cpp
	g++ -Wall -c nodo.cpp

virtualSocket.o: virtualSocket.cpp
	g++ -Wall -c virtualSocket.cpp

prepara_carpeta:
	rm -rf /tmp/p1 /tmp/p2 /tmp/p3 /tmp/p4 /tmp/p5 /tmp/p6 /tmp/p7 /tmp/p8 /tmp/p9 /tmp/p10

# Corre virtualSocket
run_socket: prepara_carpeta
	socat -d -d pty,raw,echo=0,link=/tmp/p1 pty,raw,echo=0,link=/tmp/p2 &
	socat -d -d pty,raw,echo=0,link=/tmp/p3 pty,raw,echo=0,link=/tmp/p4 &
	socat -d -d pty,raw,echo=0,link=/tmp/p5 pty,raw,echo=0,link=/tmp/p6 &
	socat -d -d pty,raw,echo=0,link=/tmp/p7 pty,raw,echo=0,link=/tmp/p8 &
	socat -d -d pty,raw,echo=0,link=/tmp/p9 pty,raw,echo=0,link=/tmp/p10 &
	socat -d -d pty,raw,echo=0,link=/tmp/p2 pty,raw,echo=0,link=/tmp/p3 &
	socat -d -d pty,raw,echo=0,link=/tmp/p4 pty,raw,echo=0,link=/tmp/p5 &
	socat -d -d pty,raw,echo=0,link=/tmp/p6 pty,raw,echo=0,link=/tmp/p7 &
	socat -d -d pty,raw,echo=0,link=/tmp/p8 pty,raw,echo=0,link=/tmp/p9 &
	socat -d -d pty,raw,echo=0,link=/tmp/p10 pty,raw,echo=0,link=/tmp/p1 &

# Ejecuta los nodos
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

# Limpia los archivos objeto
clean:
	rm *.o nodo virtualSocket