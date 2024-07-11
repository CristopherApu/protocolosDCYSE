#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "nodo.h"

void inicializar_nodo(const char* ip, const char* puerto1, const char* puerto2);
void mostrar_tabla_ruta(const Nodo* nodo);
void recibir_mensaje(char* mensaje);
void procesar_mensaje_broadcast(const char* ip_origen, int ttl);
void procesar_mensaje_unicast(const char* ip_origen, const char* ip_destino, int ttl, const char* mensaje);
void encapsular_ipv4(const char* mensaje, const char* ip_origen, const char* ip_destino, int ttl, char* paquete);
void encapsular_slip(const char* paquete, char* trama);
void enviar_mensaje(const char* ip_destino, const char* mensaje, int es_broadcast);

#endif // FUNCIONES_H