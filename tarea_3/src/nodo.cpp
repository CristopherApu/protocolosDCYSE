#include "nodo.h"
#include <algorithm> // Para std::transform
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <thread>

void recibirMensajes(int fd_in, std::vector<Ruta> &tablaRutas) {
    char buffer[256];
    while (true) {
        int n = read(fd_in, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Mensaje recibido: %s\n", buffer);
            recibirMensaje(buffer, tablaRutas);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <IP> <puerto_in> <puerto_out>\n", argv[0]);
        return 1;
    }

    int fd_in = open(argv[2], O_RDWR | O_NOCTTY);
    int fd_out = open(argv[3], O_RDWR | O_NOCTTY);

    if (fd_in < 0 || fd_out < 0) {
        perror("Error al abrir los puertos virtuales");
        return 1;
    }

    std::vector<Ruta> tablaRutas;
    std::vector<std::string> fragmentos;
    std::vector<std::string> fragmentosRecibidos;

    std::thread receiver(recibirMensajes, fd_in, std::ref(tablaRutas));
    receiver.detach();

    // Lógica principal del programa
    char tipoMensaje[256];
    char mensaje[256];
    char destino[16];

    while (true) {
        printf("Ingrese el tipo de mensaje (broadcast/unicast): ");
        scanf("%s", tipoMensaje);

        // Convertir la entrada a minúsculas para un manejo más fácil
        std::string tipoMensajeStr(tipoMensaje);
        std::transform(tipoMensajeStr.begin(), tipoMensajeStr.end(), tipoMensajeStr.begin(), ::tolower);

        if (tipoMensajeStr == "broadcast" || tipoMensajeStr == "bro" || tipoMensajeStr == "b") {
            printf("Ingrese el mensaje: ");
            getchar(); // Limpiar el buffer de entrada
            fgets(mensaje, sizeof(mensaje), stdin);
            mensaje[strcspn(mensaje, "\n")] = '\0'; // Eliminar el salto de línea al final de fgets
            manejarFragmentacion(mensaje, 50, fragmentos); // Tamaño del fragmento ajustado para pruebas
            for (const auto &fragmento : fragmentos) {
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "%s 5", fragmento.c_str());
                write(fd_out, buffer, strlen(buffer));
                printf("Mensaje enviado: %s\n", buffer); // Mensaje de depuración
            }
        } else if (tipoMensajeStr == "unicast" || tipoMensajeStr == "uni" || tipoMensajeStr == "u") {
            printf("Ingrese el mensaje: ");
            getchar(); // Limpiar el buffer de entrada
            fgets(mensaje, sizeof(mensaje), stdin);
            mensaje[strcspn(mensaje, "\n")] = '\0'; // Eliminar el salto de línea al final de fgets
            printf("Ingrese la IP de destino: ");
            scanf("%s", destino);

            // Aquí asumimos que la tabla de rutas tiene una entrada para la IP destino
            for (const auto &ruta : tablaRutas) {
                if (ruta.ip == destino) {
                    manejarFragmentacion(mensaje, 50, fragmentos); // Tamaño del fragmento ajustado para pruebas
                    for (const auto &fragmento : fragmentos) {
                        char buffer[256];
                        snprintf(buffer, sizeof(buffer), "%s 5", fragmento.c_str());
                        write(fd_out, buffer, strlen(buffer));
                        printf("Mensaje enviado: %s\n", buffer); // Mensaje de depuración
                        // Simular la recepción del fragmento
                        fragmentosRecibidos.push_back(fragmento);
                    }
                    break;
                }
            }
        } else {
            printf("Tipo de mensaje no válido.\n");
        }

        // Ensamblar los fragmentos recibidos
        if (!fragmentosRecibidos.empty()) {
            std::string mensajeCompleto = ensamblarFragmentos(fragmentosRecibidos);
            printf("Mensaje ensamblado: %s\n", mensajeCompleto.c_str());
            fragmentosRecibidos.clear(); // Limpiar los fragmentos recibidos después de ensamblar
        }

        mostrarTablaRutas(tablaRutas);
        fragmentos.clear(); // Limpiar los fragmentos para la siguiente entrada
    }

    close(fd_in);
    close(fd_out);
    return 0;
}