#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "slip.h"
#include "serial.h"
#include "ipv4.h"

#define MAX_IP_LENGTH 16
#define BUFFER_SIZE 1024

uint32_t convertir_ip(const char* ip_str);
void procesar_paquete(const IPv4Packet& paquete, const char* puerto_tx, int fd_tx);
void enviar_mensaje(int fd_tx, uint32_t ip_destino, const std::vector<unsigned char>& data, uint8_t ttl, uint16_t id);

uint32_t current_ip; // Definición de current_ip

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <IP_del_nodo> <puerto_tx> <puerto_rx>\n", argv[0]);
        return 1;
    }

    char ip[MAX_IP_LENGTH];
    char *puerto_tx, *puerto_rx;

    strncpy(ip, argv[1], MAX_IP_LENGTH - 1);
    ip[MAX_IP_LENGTH - 1] = '\0';
    puerto_tx = argv[2];
    puerto_rx = argv[3];

    // Convertir la IP del nodo a formato uint32_t
    current_ip = convertir_ip(ip);

    printf("Nodo iniciado con IP: %s\n", ip);
    printf("Puerto de envío: %s\n", puerto_tx);
    printf("Puerto de recepción: %s\n", puerto_rx);

    // Abrir puertos seriales
    int fd_tx = openPort(puerto_tx, B9600);
    int fd_rx = openPort(puerto_rx, B9600);

    if (fd_tx == -1) {
        printf("Error al abrir el puerto de envío %s\n", puerto_tx);
        return 1;
    }

    if (fd_rx == -1) {
        printf("Error al abrir el puerto de recepción %s\n", puerto_rx);
        return 1;
    }

    printf("Puertos seriales abiertos correctamente\n");

    // Buffer para recibir datos
    BYTE buffer[BUFFER_SIZE];

    fd_set readfds;
    int max_fd = fd_rx > STDIN_FILENO ? fd_rx : STDIN_FILENO;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd_rx, &readfds);
        FD_SET(STDIN_FILENO, &readfds);

        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select error");
            break;
        }

        // Leer datos del puerto RX
        if (FD_ISSET(fd_rx, &readfds)) {
            int bytes_read = readPort(fd_rx, buffer, BUFFER_SIZE, 1000);
            if (bytes_read > 0) {
                printf("Datos recibidos en el puerto de recepción\n");
                // Convertir los datos leídos a un vector
                std::vector<unsigned char> encoded_data(buffer, buffer + bytes_read);

                // Decodificar los datos SLIP
                std::vector<unsigned char> decoded_data = slip_decode(encoded_data);

                // Decapsular el paquete IPv4 modificado
                IPv4Packet paquete = decapsulate_ipv4(decoded_data);

                // Mostrar el paquete recibido para depuración
                printf("Mensaje recibido en nodo %s: %s\n", ip, paquete.data.data());

                // Procesar el paquete
                procesar_paquete(paquete, puerto_tx, fd_tx);
            }
        }

        // Leer entrada del usuario
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char input_buffer[BUFFER_SIZE];
            if (fgets(input_buffer, BUFFER_SIZE, stdin) != NULL) {
                // Eliminar el carácter de nueva línea
                size_t len = strlen(input_buffer);
                if (len > 0 && input_buffer[len-1] == '\n') {
                    input_buffer[len-1] = '\0';
                }

                printf("Ingrese tipo de mensaje (unicast/broadcast): ");
                char tipo_mensaje[BUFFER_SIZE];
                fgets(tipo_mensaje, BUFFER_SIZE, stdin);
                tipo_mensaje[strcspn(tipo_mensaje, "\n")] = '\0';

                if (strcmp(tipo_mensaje, "unicast") == 0) {
                    printf("Ingrese la IP de destino: ");
                    char ip_destino_str[BUFFER_SIZE];
                    fgets(ip_destino_str, BUFFER_SIZE, stdin);
                    ip_destino_str[strcspn(ip_destino_str, "\n")] = '\0';
                    uint32_t ip_destino = convertir_ip(ip_destino_str);

                    // Enviar mensaje unicast
                    std::vector<unsigned char> data(input_buffer, input_buffer + strlen(input_buffer));
                    enviar_mensaje(fd_tx, ip_destino, data, 64, rand() % 65536);
                } else if (strcmp(tipo_mensaje, "broadcast") == 0) {
                    // Enviar mensaje broadcast
                    std::vector<unsigned char> data(input_buffer, input_buffer + strlen(input_buffer));
                    enviar_mensaje(fd_tx, 0xFFFFFFFF, data, 4, rand() % 65536); // Broadcast con TTL 4
                } else {
                    printf("Tipo de mensaje no reconocido.\n");
                }
            }
        }
    }

    // Cerrar puertos seriales
    closePort(fd_tx);
    closePort(fd_rx);

    return 0;
}

uint32_t convertir_ip(const char* ip_str) {
    uint32_t ip;
    unsigned int b1, b2, b3, b4;
    sscanf(ip_str, "%u.%u.%u.%u", &b1, &b2, &b3, &b4);
    ip = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
    return ip;
}

void procesar_paquete(const IPv4Packet& paquete, const char* puerto_tx, int fd_tx) {
    if (paquete.ttl > 1) {
        IPv4Packet nuevo_paquete = paquete;
        nuevo_paquete.ttl--;

        if (paquete.dest_ip == 0xFFFFFFFF) { // Broadcast
            printf("Broadcast recibido de IP: %u\n", paquete.src_ip);
        } else if (paquete.dest_ip == current_ip) { // Unicast
            printf("Unicast recibido de IP: %u, Mensaje: %s\n", paquete.src_ip, paquete.data.data());
            return;
        }

        std::vector<unsigned char> encoded_data = slip_encode(encapsulate_ipv4(nuevo_paquete));
        writePort(fd_tx, encoded_data.data(), encoded_data.size());
    } else if (paquete.dest_ip == current_ip) { // Unicast y TTL ha llegado a 1
        printf("Unicast recibido de IP: %u, Mensaje: %s\n", paquete.src_ip, paquete.data.data());
    }
}

void enviar_mensaje(int fd_tx, uint32_t ip_destino, const std::vector<unsigned char>& data, uint8_t ttl, uint16_t id) {
    IPv4Packet paquete;
    paquete.ttl = ttl;
    paquete.id = id;
    paquete.src_ip = current_ip;
    paquete.dest_ip = ip_destino;
    paquete.data = data;

    std::vector<unsigned char> encoded_data = slip_encode(encapsulate_ipv4(paquete));
    writePort(fd_tx, encoded_data.data(), encoded_data.size());
}