#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// Definición de la estructura de la tabla de rutas
struct Ruta {
    char ip[16];
    int puerto;
    int ttl;
};

// Declaraciones de funciones
void enviarMensaje(const char* tipo, const char* mensaje, const char* destino, int puerto, std::vector<Ruta> &tablaRutas);
void recibirMensaje(const char* mensaje, std::vector<Ruta> &tablaRutas);
void mostrarTablaRutas(const std::vector<Ruta> &tablaRutas);

#endif