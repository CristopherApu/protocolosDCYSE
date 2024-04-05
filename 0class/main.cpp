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