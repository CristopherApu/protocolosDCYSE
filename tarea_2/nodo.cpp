#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <arpa/inet.h>
#include "slip.h"
#include "ipv4.h"

void send_message(const IPv4Packet& packet, const char* port) {
    std::vector<unsigned char> encoded_packet = slip_encode(std::vector<unsigned char>(
        reinterpret_cast<const unsigned char*>(&packet),
        reinterpret_cast<const unsigned char*>(&packet) + sizeof(packet)
    ));

    int fd = open(port, O_WRONLY | O_NOCTTY);
    if (fd == -1) {
        perror("Error abriendo el puerto");
        return;
    }

    write(fd, encoded_packet.data(), encoded_packet.size());
    close(fd);
}

void receive_message(const char* port) {
    int fd = open(port, O_RDONLY | O_NOCTTY);
    if (fd == -1) {
        perror("Error abriendo el puerto");
        return;
    }

    std::vector<unsigned char> buffer(2048);
    int n = read(fd, buffer.data(), buffer.size());
    close(fd);

    if (n > 0) {
        buffer.resize(n);
        std::vector<unsigned char> decoded_packet = slip_decode(buffer);
        IPv4Packet* packet = reinterpret_cast<IPv4Packet*>(decoded_packet.data());
        // Procesa el paquete recibido...
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <IP> <puerto_tx> <puerto_rx>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    const char* port_tx = argv[2];
    const char* port_rx = argv[3];

    IPv4Packet packet;
    packet.ip_source = inet_addr(ip);
    // Configura el resto del paquete...

    // Ejemplo de envío y recepción de mensajes
    send_message(packet, port_tx);
    receive_message(port_rx);

    return 0;
}
