#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializar_nodo(const char* ip, const char* puerto1, const char* puerto2) {
    strcpy(nodo.ip, ip);
    nodo.num_rutas = 0;
    // Inicialización adicional si es necesario
}

void mostrar_tabla_ruta(const Nodo* nodo) {
    printf("Tabla de Ruta:\n");
    for (int i = 0; i < nodo->num_rutas; ++i) {
        printf("Nodo: %s, IP: %s, Puerto1: %d, Puerto2: %d, TTL: %d\n",
            nodo->tabla_ruta[i].nombre,
            nodo->tabla_ruta[i].ip,
            nodo->tabla_ruta[i].puerto1,
            nodo->tabla_ruta[i].puerto2,
            nodo->tabla_ruta[i].ttl);
    }
}

void encapsular_ipv4(const char* mensaje, const char* ip_origen, const char* ip_destino, int ttl, char* paquete) {
    sprintf(paquete, "IPV4|%s|%s|%d|%s", ip_origen, ip_destino, ttl, mensaje);
}

void encapsular_slip(const char* paquete, char* trama) {
    sprintf(trama, "SLIP|%s|END", paquete);
}

void recibir_mensaje(char* mensaje) {
    // Lógica para recibir mensajes
    char ip_origen[16];
    char ip_destino[16];
    int ttl;

    // Desencapsular el mensaje (simplificado)
    sscanf(mensaje, "IPV4|%15[^|]|%15[^|]|%d|%s", ip_origen, ip_destino, &ttl, mensaje);

    // Procesar mensaje
    if (strcmp(ip_destino, IP_BROADCAST) == 0) {
        procesar_mensaje_broadcast(ip_origen, ttl);
    } else {
        procesar_mensaje_unicast(ip_origen, ip_destino, ttl, mensaje);
    }
}

void procesar_mensaje_broadcast(const char* ip_origen, int ttl) {
    if (ttl <= 0) return;

    int i;
    int encontrado = 0;
    for (i = 0; i < nodo.num_rutas; i++) {
        if (strcmp(nodo.tabla_ruta[i].ip, ip_origen) == 0) {
            encontrado = 1;
            if (nodo.tabla_ruta[i].ttl > ttl) {
                nodo.tabla_ruta[i].ttl = ttl;
                printf("Tabla de ruta actualizada para %s\n", ip_origen);
            }
            break;
        }
    }
    if (!encontrado && nodo.num_rutas < TABLE_SIZE) {
        strcpy(nodo.tabla_ruta[nodo.num_rutas].ip, ip_origen);
        nodo.tabla_ruta[nodo.num_rutas].puerto1 = 2;
        nodo.tabla_ruta[nodo.num_rutas].puerto2 = 3;
        nodo.tabla_ruta[nodo.num_rutas].ttl = ttl;
        nodo.num_rutas++;
    }

    ttl--;
    char paquete[1500];
    encapsular_ipv4("Broadcast reenviado", nodo.tabla_ruta[0].ip, IP_BROADCAST, ttl, paquete);
    char trama[1600];
    encapsular_slip(paquete, trama);

    printf("Reenviando mensaje broadcast: %s\n", "Broadcast reenviado");
}

void procesar_mensaje_unicast(const char* ip_origen, const char* ip_destino, int ttl, const char* mensaje) {
    if (ttl <= 0) return;

    if (strcmp(ip_destino, nodo.tabla_ruta[0].ip) == 0) {
        printf("Mensaje unicast recibido de %s: %s\n", ip_origen, mensaje);
    } else {
        ttl--;
        char paquete[1500];
        encapsular_ipv4(mensaje, ip_origen, ip_destino, ttl, paquete);
        char trama[1600];
        encapsular_slip(paquete, trama);

        printf("Reenviando mensaje unicast a %s: %s\n", ip_destino, mensaje);
    }
}

void enviar_mensaje(const char* ip_destino, const char* mensaje, int es_broadcast) {
    char paquete[1500];
    if (es_broadcast) {
        encapsular_ipv4(mensaje, nodo.tabla_ruta[0].ip, IP_BROADCAST, MAX_TTL, paquete);
    } else {
        encapsular_ipv4(mensaje, nodo.tabla_ruta[0].ip, ip_destino, MAX_TTL, paquete);
    }
    char trama[1600];
    encapsular_slip(paquete, trama);
    printf("Enviando mensaje %s a %s: %s\n", es_broadcast ? "broadcast" : "unicast", ip_destino, mensaje);
}