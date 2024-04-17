#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VENDEDORES 20
#define NUMERO_FAIXAS_SALARIAIS 8
#define FLT_MAX 100000

typedef struct {
    char nome[50];
    float faturamento;
} Vendedor;

// Constantes para as faixas salariais
const float SALARIO_INICIAL[NUMERO_FAIXAS_SALARIAIS]    = {500, 600, 700, 800, 900, 1000, 1200, 1300};
const float SALARIO_FINAL[NUMERO_FAIXAS_SALARIAIS]      = {599, 699, 799, 899, 999, 1199, 1299, FLT_MAX};

int main(int argc, char *argv[]) {
    // Caminho padrão do arquivo
    char *caminho_arquivo = "./vendedores.csv";

    // Se fornecido, estabele o path para o arquivo de dados
    if (argc == 2) {
        caminho_arquivo = argv[1];
    }

    // Abre o arquivo CSV para leitura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Array para armazenar os vendedores
    Vendedor vendedores[MAX_VENDEDORES];
    
    // Array para armazenar o número de vendedores em cada faixa salarial
    int faixas[NUMERO_FAIXAS_SALARIAIS] = {0};

    // Ler os dados dos vendedores do arquivo
    int num_vendedores;
    for (num_vendedores = 0; num_vendedores < MAX_VENDEDORES; num_vendedores++) {
        char linha[100];
        if (fgets(linha, sizeof(linha), arquivo) == NULL) {
            break;
        }
        char *nome = strtok(linha, ",");
        char *faturamento_str = strtok(NULL, ",");
        if (nome != NULL && faturamento_str != NULL) {
            strcpy(vendedores[num_vendedores].nome, nome);
            vendedores[num_vendedores].faturamento = atof(faturamento_str);
        } else {
            printf("Erro: formato de linha inválido no arquivo.\n");
            break;
        }
    }

    // Fechar o arquivo
    fclose(arquivo);

    // Calcular os salários dos vendedores
    for (int i = 0; i < num_vendedores; i++) {
        float salario = 500 + 0.09 * vendedores[i].faturamento;
        for (int j = 0; j < NUMERO_FAIXAS_SALARIAIS; j++) {
            if (salario >= SALARIO_INICIAL[j] && salario <= SALARIO_FINAL[j]) {
                faixas[j]++;
                break;
            }
        }
    }

    // Exibir o número de vendedores em cada faixa salarial
    printf("Faixas Salariais:\n");
    char letra = 'a';
    for (int i = 0; i < NUMERO_FAIXAS_SALARIAIS; i++) {
        if (i == NUMERO_FAIXAS_SALARIAIS - 1) {
            printf("%c) R$ %.2f ou mais: %d vendedores\n", letra++, SALARIO_INICIAL[i], faixas[i]);
        } else {
            printf("%c) R$ %.2f a R$ %.2f: %d vendedores\n", letra++, SALARIO_INICIAL[i], SALARIO_FINAL[i], faixas[i]);
        }
    }

    return 0;
}
