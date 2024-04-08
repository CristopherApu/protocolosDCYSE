/*
#include <cstdio>

int main() {
    for (int x = 1; x <= 50; x++) {
        printf("%d ", x);
        if (x%10 == 0) {
            printf("\n");
        }
    }
    return 0;
}
*/
/*
#include <cstdio>
#include <cstring>

void convertir_a_mayuscula(char *palabra) {
    for (int i = 0; palabra[i] != '\0'; ++i) {
        if (palabra[i] >= 'a' && palabra[i] <= 'z') {
            palabra[i] -= 32;
        }
    }
}

int main() {
    char frase[100];

    printf("Introduce una frase en minúsculas: ");
    fgets(frase, sizeof(frase), stdin);

    frase[strcspn(frase, "\n")] = '\0';

    convertir_a_mayuscula(frase);

    printf("La transformación queda en: %s\n", frase);

    return 0;
}
*/
/*
#include <cstdio>

int main() {
    int numero = 14;
    printf("El numero 14 en binario es: ");
    for (int i = 7; i >= 0; i--){
        int bit = (numero >> i) & 0x01;
        printf("%d", bit);
    }
    return 0;
}
*/
#include <cstdio>
#include "struct.h"

void sum(int a, int b);
void rest(int a, int b);
void multi(float &a, float &b);
void div(float &a, float &b);

int main() {
    char op;
    printf("Hola, qué tipo de operación quisieras realizar?\n1.- Suma\n2.- Resta\n3.- División\n4.- Multiplicación\n");
    scanf(" %c", &op);

    switch (op) {
        case '1': {
            Numeros n;
            printf("Favor ingrese el primer número: ");
            scanf("%d", &n.a);
            printf("Favor ingrese el segundo número: ");
            scanf("%d", &n.b);
            sum(n.a, n.b);
            break;
        }
        case '2': {
            Numeros m;
            printf("Favor ingrese el primer número: ");
            scanf("%d", &m.a);
            printf("Favor ingrese el segundo número: ");
            scanf("%d", &m.b);
            rest(m.a, m.b);
            break;
        }
        case '3': {
            Numeros o;
            printf("Favor ingrese el primer número: ");
            scanf("%f", &o.c);
            printf("Favor ingrese el segundo número: ");
            scanf("%f", &o.d);
            div(o.c, o.d);
            break;
        }
        case '4': {
            Numeros p;
            printf("Favor ingrese el primer número: ");
            scanf("%f", &p.c);
            printf("Favor ingrese el segundo número: ");
            scanf("%f", &p.d);
            multi(p.c, p.d);
            break;
        }
        default:
            printf("Orden no identificada\n");
            break;
    }

    return 0;
}