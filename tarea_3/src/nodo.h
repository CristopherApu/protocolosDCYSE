#ifndef NODO_H
#define NODO_H

#define MAX_TTL 64
#define TABLE_SIZE 10
#define IP_BROADCAST "F.F.F.F"

typedef struct {
    char ip[16];
    int puerto1;
    int puerto2;
    int ttl;
    char nombre[16];
} TablaRuta;

typedef struct {
    char ip[16];
    TablaRuta tabla_ruta[TABLE_SIZE];
    int num_rutas;
} Nodo;

extern Nodo nodo; // Declaración de la variable global nodo

void inicializar_nodo(const char* ip, const char* puerto1, const char* puerto2);
void mostrar_tabla_ruta(const Nodo* nodo);
void recibir_mensaje(char* mensaje);
void procesar_mensaje_broadcast(const char* ip_origen, int ttl);
void procesar_mensaje_unicast(const char* ip_origen, const char* ip_destino, int ttl, const char* mensaje);
void encapsular_ipv4(const char* mensaje, const char* ip_origen, const char* ip_destino, int ttl, char* paquete);
void encapsular_slip(const char* paquete, char* trama);
void enviar_mensaje(const char* ip_destino, const char* mensaje, int es_broadcast);

#endif // NODO_H