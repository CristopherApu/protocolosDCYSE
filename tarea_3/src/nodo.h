#ifndef NODO_H
#define NODO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>

// Definición de la estructura de la tabla de rutas
struct Ruta {
    std::string ip;
    int puerto;
    int ttl;
};

// Declaraciones de funciones
void enviarMensaje(const char* tipo, const char* mensaje, const char* destino, int puerto, std::vector<Ruta> &tablaRutas);
void recibirMensaje(const char* mensaje, std::vector<Ruta> &tablaRutas);
void reenviarMensaje(const char* tipo, const char* mensaje, int puerto, int ttl, std::vector<Ruta> &tablaRutas);
void mostrarTablaRutas(const std::vector<Ruta> &tablaRutas);

#endif