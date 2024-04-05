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

void sum(int a, int b) {
    printf("Favor ingrese el primer número: ");
    scanf("%d", &a);
    printf("Favor ingrese el segundo número: ");
    scanf("%d", &b);
    int result = a + b;
    printf("El resultado de la suma es: %d\n", result);
}
void rest(int a, int b) {
    printf("Favor ingrese el primer número: ");
    scanf("%d", &a);
    printf("Favor ingrese el segundo número: ");
    scanf("%d", &b);
    int result = a - b;
    printf("El resultado de la resta es: %d\n", result);
}
void multi(float &a, float &b) {
    printf("Favor ingrese el primer número: ");
    scanf("%f", &a);
    printf("Favor ingrese el segundo número: ");
    scanf("%f", &b);
    float result = a * b;
    printf("El resultado de la multiplicación es: %.2f\n", result);
}
void div(float &a, float &b) {
    printf("Favor ingrese el primer número: ");
    scanf("%f", &a);
    printf("Favor ingrese el segundo número: ");
    scanf("%f", &b);
    if (b != 0) {
        float result = a / b;
        printf("El resultado de la división es: %.2f\n", result);
    } else {
        printf("Error: no se puede dividir por cero.\n");
    }
}

int main() {
    char op;
    printf("Hola, qué tipo de operación quisieras realizar?\n1.- Suma\n2.- Resta\n3.- División\n4.- Multiplicación\n");
    scanf(" %c", &op);
    switch (op) {
        case '1':
            sum(0, 0);
            break;
        case '2':
            rest(0, 0);
            break;
        case '3':
            float num1, num2;
            div(num1, num2);
            break;
        case '4':
            float num3, num4;
            multi(num3, num4);
            break;
        default:
            printf("Orden no identificada\n");
            break;
    }
    return 0;
}