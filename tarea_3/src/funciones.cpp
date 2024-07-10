#include "nodo.h"

void enviarMensaje(const char* tipo, const char* mensaje, const char* destino, int puerto, std::vector<Ruta> &tablaRutas) {
    printf("Enviando mensaje %s a %s:%d\n", mensaje, destino, puerto);
    int ttl = 5; // Valor TTL inicial
    reenviarMensaje(tipo, mensaje, puerto, ttl, tablaRutas);
    printf("\n"); // Salto de línea para delimitar el fin del mensaje
}

void recibirMensaje(const char* mensaje, std::vector<Ruta> &tablaRutas) {
    printf("Recibiendo mensaje: %s\n", mensaje);
    char destino[16];
    int ttl;
    sscanf(mensaje, "%15s %d", destino, &ttl);
    ttl--;
    if (ttl <= 0) {
        printf("Mensaje descartado, TTL expirado.\n");
        return;
    }
    bool rutaExistente = false;
    int puerto = 0;
    for (auto &ruta : tablaRutas) {
        if (strcmp(ruta.ip.c_str(), destino) == 0) {
            rutaExistente = true;
            puerto = ruta.puerto;
            if (ttl < ruta.ttl) {
                ruta.ttl = ttl;
                printf("Tabla de rutas actualizada para IP %s\n", destino);
            }
            break;
        }
    }
    if (!rutaExistente) {
        Ruta nuevaRuta;
        nuevaRuta.ip = destino;
        nuevaRuta.ttl = ttl;
        nuevaRuta.puerto = puerto;
        tablaRutas.push_back(nuevaRuta);
        printf("Nueva ruta añadida para IP %s\n", destino);
        puerto = nuevaRuta.puerto;
    }
    printf("Reenviando mensaje con TTL reducido a %d\n", ttl);
    reenviarMensaje("unicast", mensaje, puerto, ttl, tablaRutas);
}

void reenviarMensaje(const char* tipo, const char* mensaje, int puerto, int ttl, std::vector<Ruta> &tablaRutas) {
    if (ttl > 0) {
        printf("Reenviando mensaje %s con TTL reducido a %d por el puerto %d\n", tipo, ttl, puerto);
    }
}

void mostrarTablaRutas(const std::vector<Ruta> &tablaRutas) {
    for (const auto &ruta : tablaRutas) {
        printf("IP: %s, Puerto: %d, TTL: %d\n", ruta.ip.c_str(), ruta.puerto, ruta.ttl);
    }
}