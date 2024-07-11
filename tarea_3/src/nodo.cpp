#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

Nodo nodo; // Definición de la variable global nodo

int puerto1_fd, puerto2_fd;

void mostrar_menu() {
    printf("=== Menú Principal ===\n");
    printf("1. Enviar mensaje Broadcast\n");
    printf("2. Enviar mensaje Unicast\n");
    printf("3. Mostrar tabla de ruta\n");
    printf("4. Simular recepción de mensaje\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

void inicializar_puertos(const char* puerto1, const char* puerto2) {
    puerto1_fd = open(puerto1, O_RDWR | O_NOCTTY);
    puerto2_fd = open(puerto2, O_RDWR | O_NOCTTY);

    if (puerto1_fd < 0 || puerto2_fd < 0) {
        perror("Error al abrir los puertos");
        exit(1);
    }
}

void enviar_puerto(int fd, const char* mensaje) {
    write(fd, mensaje, strlen(mensaje));
    write(fd, "\n", 1); // Agregar un salto de línea para marcar el final del mensaje
}

void recibir_puerto(int fd, char* buffer, size_t len) {
    int n = read(fd, buffer, len);
    if (n > 0) {
        buffer[n] = '\0'; // Agregar el terminador de cadena al final
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Uso: %s <IP> <puerto1> <puerto2>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    const char* puerto1 = argv[2];
    const char* puerto2 = argv[3];

    inicializar_nodo(ip, puerto1, puerto2);
    inicializar_puertos(puerto1, puerto2);

    const char* ips[] = {"192.168.1.1", "192.168.1.2", "192.168.1.3", "192.168.1.4", "192.168.1.5"};
    const char* nombres[] = {"A", "B", "C", "D", "E"};
    for (int i = 0; i < 5; ++i) {
        strcpy(nodo.tabla_ruta[i].ip, ips[i]);
        nodo.tabla_ruta[i].puerto1 = 2 * i + 1;
        nodo.tabla_ruta[i].puerto2 = 2 * i + 2;
        nodo.tabla_ruta[i].ttl = MAX_TTL;
        strcpy(nodo.tabla_ruta[i].nombre, nombres[i]);
    }
    nodo.num_rutas = 5;

    int opcion;
    char mensaje[1500];
    char ip_destino[16];
    char buffer[1600];

    while (1) {
        mostrar_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el mensaje Broadcast: ");
                scanf(" %[^\n]s", mensaje);
                enviar_mensaje(IP_BROADCAST, mensaje, 1);
                for (int i = 0; i < nodo.num_rutas; ++i) {
                    enviar_puerto(puerto1_fd, mensaje);
                }
                break;

            case 2:
                printf("Ingrese la IP destino: ");
                scanf("%s", ip_destino);
                printf("Ingrese el mensaje Unicast: ");
                scanf(" %[^\n]s", mensaje);
                enviar_mensaje(ip_destino, mensaje, 0);
                enviar_puerto(puerto1_fd, mensaje);
                break;

            case 3:
                mostrar_tabla_ruta(&nodo);
                break;

            case 4:
                recibir_puerto(puerto1_fd, buffer, sizeof(buffer));
                recibir_mensaje(buffer);
                break;

            case 5:
                printf("Saliendo...\n");
                close(puerto1_fd);
                close(puerto2_fd);
                exit(0);

            default:
                printf("Opción no válida. Intente nuevamente.\n");
                break;
        }
    }

    return 0;
}