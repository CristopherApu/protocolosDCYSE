#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "slip.h"
#include "serial.h"

#define MAX_IP_LENGTH 16
#define BUFFER_SIZE 1024

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

    printf("Nodo iniciado con IP: %s\n", ip);
    printf("Puerto de envío: %s\n", puerto_tx);
    printf("Puerto de recepción: %s\n", puerto_rx);

    // Abrir puertos seriales
    int fd_tx = openPort(puerto_tx, B9600);
    int fd_rx = openPort(puerto_rx, B9600);

    if (fd_tx == -1 || fd_rx == -1) {
        printf("Error al abrir los puertos seriales\n");
        return 1;
    }

    // Buffer para recibir datos
    BYTE buffer[BUFFER_SIZE];

    while (1) {
        // Leer datos del puerto RX
        int bytes_read = readPort(fd_rx, buffer, BUFFER_SIZE, 1000);

        if (bytes_read > 0) {
            // Convertir los datos leídos a un vector
            std::vector<unsigned char> encoded_data(buffer, buffer + bytes_read);

            // Decodificar los datos SLIP
            std::vector<unsigned char> decoded_data = slip_decode(encoded_data);

            // TODO: Procesar el paquete IPv4 modificado
            // - Verificar si es broadcast o unicast
            // - Manejar TTL
            // - Reenviar si es necesario

            // Ejemplo de reenvío (esto debe ser modificado según la lógica requerida)
            std::vector<unsigned char> encoded_output = slip_encode(decoded_data);
            writePort(fd_tx, encoded_output.data(), encoded_output.size());
        }

        // TODO: Implementar lógica para enviar mensajes
    }

    // Cerrar puertos seriales
    closePort(fd_tx);
    closePort(fd_rx);

    return 0;
}