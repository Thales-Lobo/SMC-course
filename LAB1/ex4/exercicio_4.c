#include <stdio.h>

#define TAMANHO_CONJUNTO 100

// Exibição do histograma
void exibir_histograma(int frequencias[]) {
    printf("Histograma de frequências:\n");
    for (int i = 1; i <= 9; i++) {
        printf("%d: ", i);
        for (int j = 0; j < frequencias[i]; j++) {
            printf("█");
        }
        double percentual = (double)frequencias[i] / TAMANHO_CONJUNTO * 100;
        printf(" (%d, %.2f%%)\n", frequencias[i], percentual);
    }
}

int main() {
    // Definindo o conjunto de dados
    int conjunto_dados[TAMANHO_CONJUNTO] = {6, 7, 8, 9, 8, 7, 8, 9, 8, 9, 7, 8, 9, 5, 9, 8, 7, 8, 7, 8,
                                            6, 7, 8, 9, 3, 9, 8, 7, 8, 7, 7, 8, 9, 8, 9, 8, 9, 7, 8,
                                            9, 6, 7, 8, 7, 8, 7, 9, 8, 9, 2, 7, 8, 9, 8, 9, 8, 9, 7,
                                            5, 3, 5, 6, 7, 2, 5, 3, 9, 4, 6, 4, 7, 8, 9, 6, 8, 7, 8,
                                            9, 7, 8, 7, 4, 4, 2, 5, 3, 8, 7, 5, 6, 4, 5, 6, 1, 6, 5,
                                            7, 8, 7};

    // Inicializando variáveis para calcular a média
    double soma = 0.0;
    for (int i = 0; i < TAMANHO_CONJUNTO; i++) {
        soma += conjunto_dados[i];
    }
    double media = soma / TAMANHO_CONJUNTO;

    // Imprimindo a média
    printf("Media: %.2f\n", media);

    // Inicializando o array do histograma
    int frequencias[10] = {0};

    // Calculando as frequências de cada número no conjunto de dados
    for (int i = 0; i < TAMANHO_CONJUNTO; i++) {
        frequencias[conjunto_dados[i]]++;
    }

    // Printa o histograma
    exibir_histograma(frequencias);

    return 0;
}
