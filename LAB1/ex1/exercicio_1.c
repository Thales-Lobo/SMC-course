#include <stdio.h>
#include <stdlib.h>

float validar_e_converter_argumento(const char *arg) {
    char *endptr;
    float valor = strtod(arg, &endptr);
    if (*endptr != '\0' || valor <= 0) {
        printf("Erro: O argumento '%s' deve ser um número positivo não nulo!\n", arg);
        exit(EXIT_FAILURE);
    }
    return valor;
}

int main(int argc, char *argv[]) {
    // Verifica se o número de argumentos está correto
    if (argc != 4) {
        printf("Uso: %s <consumo_medio[Km/L]> <tempo_gasto[h]> <velocidade_media[Km/h]>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Converte e valida os argumentos
    float consumo_medio     = validar_e_converter_argumento(argv[1]);
    float tempo_gasto       = validar_e_converter_argumento(argv[2]);
    float velocidade_media  = validar_e_converter_argumento(argv[3]);

    // Calcula a distância percorrida em Km
    float distancia_percorrida = tempo_gasto * velocidade_media;

    // Calcula a quantidade de combustível utilizada em litros
    float combustivel_utilizado = distancia_percorrida / consumo_medio;

    // Exibe os resultados
    printf("Distancia percorrida: %.2f [Km]\n", distancia_percorrida);
    printf("Combustivel utilizado: %.2f litros\n", combustivel_utilizado);

    return 0;
}
