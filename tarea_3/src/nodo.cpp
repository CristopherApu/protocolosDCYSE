#include "nodo.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <IP> <puerto1> <puerto2>\n", argv[0]);
        return 1;
    }

    int puerto1 = atoi(argv[2]);

    std::vector<Ruta> tablaRutas;

    // Lógica principal del programa
    char tipoMensaje[10];
    char mensaje[256];
    char destino[16];
    int puertoDestino;

    while (true) {
        printf("Ingrese el tipo de mensaje (broadcast/unicast): ");
        scanf("%s", tipoMensaje);

        if (strcmp(tipoMensaje, "broadcast") == 0) {
            printf("Ingrese el mensaje: ");
            getchar(); // Limpiar el buffer de entrada
            fgets(mensaje, sizeof(mensaje), stdin);
            // Eliminar el salto de línea al final de fgets
            mensaje[strcspn(mensaje, "\n")] = '\0';
            enviarMensaje(tipoMensaje, mensaje, "F.F.F.F", puerto1, tablaRutas);
        } else if (strcmp(tipoMensaje, "unicast") == 0) {
            printf("Ingrese el mensaje: ");
            getchar(); // Limpiar el buffer de entrada
            fgets(mensaje, sizeof(mensaje), stdin);
            // Eliminar el salto de línea al final de fgets
            mensaje[strcspn(mensaje, "\n")] = '\0';
            printf("Ingrese la IP de destino: ");
            scanf("%s", destino);
            printf("Ingrese el puerto de destino: ");
            scanf("%d", &puertoDestino);
            enviarMensaje(tipoMensaje, mensaje, destino, puertoDestino, tablaRutas);
        } else {
            printf("Tipo de mensaje no válido.\n");
        }

        mostrarTablaRutas(tablaRutas);
    }

    return 0;
}