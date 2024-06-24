#include "slip.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

#define TAMANIO_BUFFER 1500
#define TTL_INICIAL 10

// Estructura para representar un mensaje IPv4 modificado
struct MensajeIPv4 {
    unsigned char tipo;         // Tipo de mensaje (Unicast o Broadcast)
    unsigned char ttl;          // Tiempo de vida del paquete
    unsigned short identificador;// Identificador único del mensaje
    unsigned char suma_verificacion; // Suma de verificación de la cabecera IPv4
    unsigned int ip_origen;     // IP de origen (4 bytes)
    unsigned int ip_destino;    // IP de destino (4 bytes)
    std::vector<unsigned char> datos; // Datos del mensaje
};

// Función para enviar un mensaje a través del puerto especificado
void enviar_mensaje(const char* puerto, const std::vector<unsigned char>& mensaje) {
    int fd = open(puerto, O_WRONLY);
    if (fd == -1) {
        perror("Error abriendo el puerto para escribir");
        exit(1);
    }
    write(fd, mensaje.data(), mensaje.size());
    close(fd);
}

// Función para recibir un mensaje del puerto especificado
std::vector<unsigned char> recibir_mensaje(const char* puerto) {
    int fd = open(puerto, O_RDONLY);
    if (fd == -1) {
        perror("Error abriendo el puerto para leer");
        exit(1);
    }
    std::vector<unsigned char> buffer(TAMANIO_BUFFER);
    int n = read(fd, buffer.data(), TAMANIO_BUFFER);
    buffer.resize(n);
    close(fd);
    return buffer;
}

// Función para encapsular un mensaje en el protocolo IPv4 modificado
std::vector<unsigned char> encapsular_ipv4(const MensajeIPv4& mensaje) {
    std::vector<unsigned char> paquete;

    paquete.push_back(mensaje.tipo);
    paquete.push_back(mensaje.ttl);
    paquete.push_back((mensaje.identificador >> 8) & 0xFF);
    paquete.push_back(mensaje.identificador & 0xFF);
    paquete.push_back(mensaje.suma_verificacion);
    
    // IP de origen
    paquete.push_back((mensaje.ip_origen >> 24) & 0xFF);
    paquete.push_back((mensaje.ip_origen >> 16) & 0xFF);
    paquete.push_back((mensaje.ip_origen >> 8) & 0xFF);
    paquete.push_back(mensaje.ip_origen & 0xFF);
    
    // IP de destino
    paquete.push_back((mensaje.ip_destino >> 24) & 0xFF);
    paquete.push_back((mensaje.ip_destino >> 16) & 0xFF);
    paquete.push_back((mensaje.ip_destino >> 8) & 0xFF);
    paquete.push_back(mensaje.ip_destino & 0xFF);

    // Datos del mensaje
    paquete.insert(paquete.end(), mensaje.datos.begin(), mensaje.datos.end());

    return paquete;
}

// Función para manejar el mensaje recibido
void manejar_mensaje(const std::vector<unsigned char>& mensaje, const char* ip_local, const char* puerto_tx) {
    // Decodificar el mensaje con SLIP
    std::vector<unsigned char> mensaje_decodificado = slip_decodificar(mensaje);

    // Extraer campos de la cabecera IPv4 modificado
    MensajeIPv4 ipv4;
    ipv4.tipo = mensaje_decodificado[0];
    ipv4.ttl = mensaje_decodificado[1];
    ipv4.identificador = (mensaje_decodificado[2] << 8) | mensaje_decodificado[3];
    ipv4.suma_verificacion = mensaje_decodificado[4];
    
    // IP de origen (4 bytes)
    ipv4.ip_origen = (mensaje_decodificado[5] << 24) | (mensaje_decodificado[6] << 16) |
                     (mensaje_decodificado[7] << 8) | mensaje_decodificado[8];
    
    // IP de destino (4 bytes)
    ipv4.ip_destino = (mensaje_decodificado[9] << 24) | (mensaje_decodificado[10] << 16) |
                      (mensaje_decodificado[11] << 8) | mensaje_decodificado[12];

    // Datos del mensaje
    ipv4.datos.assign(mensaje_decodificado.begin() + 13, mensaje_decodificado.end());

    // Determinar el tipo de mensaje y procesarlo
    if (ipv4.tipo == 0xFF) { // Broadcast
        if (ipv4.ip_destino == ipv4.ip_origen) {
            printf("Mensaje Broadcast recibido y descartado (proveniente de este nodo).\n");
        } else {
            printf("Mensaje Broadcast recibido desde la IP %d.%d.%d.%d:\n",
                   (ipv4.ip_origen >> 24) & 0xFF, (ipv4.ip_origen >> 16) & 0xFF,
                   (ipv4.ip_origen >> 8) & 0xFF, ipv4.ip_origen & 0xFF);
            printf("Contenido del mensaje: %s\n", ipv4.datos.data());

            // Reducir TTL y reenviar el mensaje
            if (ipv4.ttl > 0) {
                ipv4.ttl--;
                std::vector<unsigned char> paquete = encapsular_ipv4(ipv4);
                std::vector<unsigned char> paquete_slip = slip_codificar(paquete);
                enviar_mensaje(puerto_tx, paquete_slip);
                printf("Mensaje Broadcast reenviado por el puerto %s.\n", puerto_tx);
            } else {
                printf("TTL agotado. No se reenvía el mensaje Broadcast.\n");
            }
        }
    } else { // Unicast
        if (ipv4.ip_destino == std::strtoul(ip_local, NULL, 0)) {
            printf("Mensaje Unicast recibido desde la IP %d.%d.%d.%d:\n",
                   (ipv4.ip_origen >> 24) & 0xFF, (ipv4.ip_origen >> 16) & 0xFF,
                   (ipv4.ip_origen >> 8) & 0xFF, ipv4.ip_origen & 0xFF);
            printf("Contenido del mensaje: %s\n", ipv4.datos.data());
        } else {
            printf("Mensaje Unicast no dirigido a esta IP. Reenviando.\n");

            // Reducir TTL y reenviar el mensaje
            if (ipv4.ttl > 0) {
                ipv4.ttl--;
                std::vector<unsigned char> paquete = encapsular_ipv4(ipv4);
                std::vector<unsigned char> paquete_slip = slip_codificar(paquete);
                enviar_mensaje(puerto_tx, paquete_slip);
                printf("Mensaje Unicast reenviado por el puerto %s.\n", puerto_tx);
            } else {
                printf("TTL agotado. No se reenvía el mensaje Unicast.\n");
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Uso: %s <IP del nodo> <Puerto TX> <Puerto RX>\n", argv[0]);
        return 1;
    }

    const char* ip_local = argv[1];
    const char* puerto_tx = argv[2];
    const char* puerto_rx = argv[3];

    // Este ejemplo solo recibe y reenvía mensajes indefinidamente
    while (true) {
        std::vector<unsigned char> mensaje_recibido = recibir_mensaje(puerto_rx);
        manejar_mensaje(mensaje_recibido, ip_local, puerto_tx);
    }

    return 0;
}