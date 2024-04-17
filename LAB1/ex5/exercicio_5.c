#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_STRING_LENGTH 100
#define RAISE_VALUE 10

// Definição da estrutura Employee
typedef struct {
    char first_name[MAX_STRING_LENGTH];
    char last_name[MAX_STRING_LENGTH];
    char birth_date[MAX_STRING_LENGTH];
    char position[MAX_STRING_LENGTH];
    float base_salary;
} Employee;

// Função para conceder aumento de salário
void paymentRaise(Employee *emp, float raise) {
    emp->base_salary *= (1 + raise / 100);
}

// Função para exibir informações do funcionário
void showInfo(Employee emp) {
    printf("First Name: %s\n", emp.first_name);
    printf("Last Name: %s\n", emp.last_name);
    printf("Birth Date: %s\n", emp.birth_date);
    printf("Position: %s\n", emp.position);
    printf("Base Salary: %.2f\n", emp.base_salary);
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Caminho padrão do arquivo
    char *file_path = "./employees.csv";

    // Se fornecido, estabele o path para o arquivo de dados
    if (argc == 2) {
        file_path = argv[1];
    }

    // Abre arquivo CSV
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Array to store employees
    Employee employees[MAX_EMPLOYEES];
    int num_employees = 0;

    // Read data from the CSV file
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        strcpy(employees[num_employees].first_name, token);

        token = strtok(NULL, ",");
        strcpy(employees[num_employees].last_name, token);

        token = strtok(NULL, ",");
        strcpy(employees[num_employees].birth_date, token);

        token = strtok(NULL, ",");
        strcpy(employees[num_employees].position, token);

        token = strtok(NULL, ",");
        employees[num_employees].base_salary = atof(token);

        num_employees++;
    }

    // Fecha o arquivo original
    fclose(file);

    // Exibir informações originais do funcionário
    printf("Informações originais dos funcionários:\n");
    for (int i = 1; i < num_employees; i++) {
        showInfo(employees[i]);
    }

    // Da um aumento fixo a todos os funcionários
    for (int i = 0; i < num_employees; i++) {
        paymentRaise(&employees[i], RAISE_VALUE);
    }

    // Exibir informações atualizadas sobre os funcionários
    printf("Informações atualizadas dos funcionários:\n");
    for (int i = 1; i < num_employees; i++) {
        showInfo(employees[i]);
    }

    // Salvar informações atualizadas dos funcionários em um novo arquivo CSV
    FILE *updated_file = fopen("updated_employees.csv", "w");
    if (updated_file == NULL) {
        printf("Erro ao criar arquivo atualizado!\n");
        return 1;
    }

    // Gravar dados no arquivo CSV atualizado
    for (int i = 0; i < num_employees; i++) {
        fprintf(updated_file, "%s,%s,%s,%s,%.2f\n", employees[i].first_name, employees[i].last_name, employees[i].birth_date, employees[i].position, employees[i].base_salary);
    }

    // Fecha o arquivo atualizado
    fclose(updated_file);

    printf("As informações atualizadas dos funcionários foram salvas em 'updated_employees.csv'!\n");

    return 0;
}
