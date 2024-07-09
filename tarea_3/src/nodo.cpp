#include "nodo.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <IP> <puerto1> <puerto2>\n", argv[0]);
        return 1;
    }

    const char* ip = argv[1];
    int puerto1 = atoi(argv[2]);
    int puerto2 = atoi(argv[3]);

    std::vector<Ruta> tablaRutas;

    // Lógica principal del programa
    // Aquí irán las funciones para enviar y recibir mensajes, así como para actualizar la tabla de rutas

    return 0;
}

void enviarMensaje(const char* tipo, const char* mensaje, const char* destino, int puerto, std::vector<Ruta> &tablaRutas) {
    // Implementación de la función para enviar mensajes
}

void recibirMensaje(const char* mensaje, std::vector<Ruta> &tablaRutas) {
    // Implementación de la función para recibir mensajes
}

void mostrarTablaRutas(const std::vector<Ruta> &tablaRutas) {
    // Implementación de la función para mostrar la tabla de rutas
    for (const auto &ruta : tablaRutas) {
        printf("IP: %s, Puerto: %d, TTL: %d\n", ruta.ip, ruta.puerto, ruta.ttl);
    }
}