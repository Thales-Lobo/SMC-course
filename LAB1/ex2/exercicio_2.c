#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    // Array armazenador da linha de texto
    char linha[101];
    
    // Captura da linha de texto
    printf("Digite sua linha de texto (máximo 100 caracteres): ");
    if (scanf("%100[^\n]", linha) != 1) {
        printf("Erro: entrada inválida.\n");
        exit(EXIT_FAILURE);
    }

    // Verifica se a linha de texto excedeu o limite de 100 caracteres
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    if (linha[100] != '\0') {
        printf("Erro: linha de texto excede o limite de 100 caracteres.\n");
        exit(EXIT_FAILURE);
    }
    
    // Converte as letras em maiúsculas e exibir
    printf("\nLinha em maiúsculas: ");
    for (int i = 0; linha[i] != '\0'; i++) {
        printf("%c", toupper(linha[i]));
    }
    
    // Converte as letras em minúsculas e exibir
    printf("\nLinha em minúsculas: ");
    for (int i = 0; linha[i] != '\0'; i++) {
        printf("%c", tolower(linha[i]));
    }
    
    printf("\n");
    
    return 0;
}
