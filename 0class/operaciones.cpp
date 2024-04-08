#include <cstdio>
#include "struct.h" // Incluir el archivo de encabezado que contiene la declaración de las estructuras

// Funciones que utilizan las estructuras

void sum(int a, int b) {
    int result = a + b;
    printf("El resultado de la suma es: %d\n", result);
}

void rest(int a, int b) {
    int result = a - b;
    printf("El resultado de la resta es: %d\n", result);
}

void multi(float &a, float &b) {
    float result = a * b;
    printf("El resultado de la multiplicación es: %.2f\n", result);
}

void div(float &a, float &b) {
    if (b != 0) {
        float result = a / b;
        printf("El resultado de la división es: %.2f\n", result);
    } else {
        printf("Error: no se puede dividir por cero.\n");
    }
}