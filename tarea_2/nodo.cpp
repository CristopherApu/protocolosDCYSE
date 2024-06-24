#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <cerrno>
#include "slip.h"

#define BUFFER_SIZE 1024

// Enumeración para tipos de mensaje
enum MessageType {
    UNICAST,
    BROADCAST
};

// Función para determinar el tipo de mensaje
MessageType determinar_tipo_mensaje(const std::vector<unsigned char>& mensaje) {
    // Aquí podrías implementar tu propia lógica para determinar el tipo de mensaje
    if (mensaje.size() == 0) {
        // Si el mensaje está vacío, retornar BROADCAST por defecto (ejemplo)
        return BROADCAST;
    }
    
    // Ejemplo simple: Si el primer byte del mensaje es 0x01, considerarlo como Unicast
    if (mensaje[0] == 0x01) {
        return UNICAST;
    } else {
        return BROADCAST;
    }
}

// Función para manejar el mensaje recibido
void manejar_mensaje(const std::vector<unsigned char>& mensaje, const char* puerto_tx, const char* puerto_rx) {
    // Aquí podrías implementar el envío del mensaje a través de los puertos TX y RX
    // En este ejemplo, simplemente se imprime el tipo de mensaje recibido
    MessageType tipo_mensaje = determinar_tipo_mensaje(mensaje);
    
    switch (tipo_mensaje) {
        case UNICAST:
            printf("Mensaje recibido: Tipo UNICAST\n");
            // Aquí podrías implementar la lógica específica para mensajes UNICAST
            // Por ejemplo, enviar el mensaje al puerto TX indicado
            printf("Enviando mensaje al puerto TX: %s\n", puerto_tx);
            break;
        case BROADCAST:
            printf("Mensaje recibido: Tipo BROADCAST\n");
            // Aquí podrías implementar la lógica específica para mensajes BROADCAST
            // Por ejemplo, retransmitir el mensaje a través de varios puertos RX
            printf("Retransmitiendo mensaje a través del puerto RX: %s\n", puerto_rx);
            break;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Uso: %s <IP del nodo> <Puerto TX> <Puerto RX>\n", argv[0]);
        return 1;
    } else if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("MANUAL DE USUARIO:\n");
        printf("-------------------\n");
        printf(" Se recomienda crear una carpeta temporal 'tmp' para almacenar los enlaces a los puertos virtuales. [mkdir tmp]\n");
        printf("\t Modo de Uso:\n");
        printf("\t\t1-.\t%s\n", argv[0]);
        printf("\t\t2-.\t%s puerto1 puerto2\n\n", argv[0]);
        printf("\t Ejemplo:\n");
        printf("\t\t2-.\t%s tmp/p1 tmp/p2\n", argv[0]);
        return 0;
    } else if (argc == 4) {
        const char* puerto_tx = argv[2];
        const char* puerto_rx = argv[3];
        
        std::vector<unsigned char> mensaje = {0x01, 0x02}; // Ejemplo de mensaje
        
        manejar_mensaje(mensaje, puerto_tx, puerto_rx);
        
    } else {
        fprintf(stderr, "Error de argumentos!\n");
        fprintf(stderr, "Use: %s -h\n", argv[0]);
        return 1;
    }

    return 0;
}