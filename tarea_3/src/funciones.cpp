#include "nodo.h"
#include <fcntl.h>
#include <unistd.h>

void enviarMensaje(const char* tipo, const char* mensaje, const char* destino, int puerto, std::vector<Ruta> &tablaRutas) {
    int ttl = 5; // Valor TTL inicial
    reenviarMensaje(tipo, mensaje, puerto, ttl, tablaRutas);
}

void recibirMensaje(const char* mensaje, std::vector<Ruta> &tablaRutas) {
    char destino[16];
    int ttl;
    sscanf(mensaje, "%15s %d", destino, &ttl);
    ttl--;
    if (ttl <= 0) {
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
        puerto = nuevaRuta.puerto;
    }
    reenviarMensaje("unicast", mensaje, puerto, ttl, tablaRutas);
}

void reenviarMensaje(const char* tipo, const char* mensaje, int puerto, int ttl, std::vector<Ruta> &tablaRutas) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s %d", mensaje, ttl);
    for (const auto &ruta : tablaRutas) {
        int fd_out = open(ruta.ip.c_str(), O_RDWR | O_NOCTTY);
        if (fd_out >= 0) {
            write(fd_out, buffer, strlen(buffer));
            close(fd_out);
        }
    }
}

void mostrarTablaRutas(const std::vector<Ruta> &tablaRutas) {
    for (const auto &ruta : tablaRutas) {
        printf("IP: %s, Puerto: %d, TTL: %d\n", ruta.ip.c_str(), ruta.puerto, ruta.ttl);
    }
}

void manejarFragmentacion(const char* mensaje, int tamanoFragmento, std::vector<std::string> &fragmentos) {
    int longitudMensaje = strlen(mensaje);
    for (int i = 0; i < longitudMensaje; i += tamanoFragmento) {
        fragmentos.push_back(std::string(mensaje + i, mensaje + std::min(i + tamanoFragmento, longitudMensaje)));
    }
}

std::string ensamblarFragmentos(const std::vector<std::string> &fragmentos) {
    std::string mensajeCompleto;
    for (const auto& fragmento : fragmentos) {
        mensajeCompleto += fragmento;
    }
    return mensajeCompleto;
}