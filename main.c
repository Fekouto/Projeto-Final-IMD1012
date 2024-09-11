
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 100
#define MAX_COLUMNS 10
#define MAX_NAME_LENGTH 50
#define MAX_RECORDS 100
#define TABLES_FILE "tables_list.dat"


typedef struct {
    char name[MAX_NAME_LENGTH];
    char type[MAX_NAME_LENGTH];
} Column;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int num_columns;
    Column columns[MAX_COLUMNS];
    char primary_key[MAX_NAME_LENGTH];
} Table;


typedef struct {
    char values[MAX_COLUMNS][MAX_NAME_LENGTH];
} Record;


Table tables[MAX_TABLES];
int num_tables = 0;


void create_table();
void list_tables();
void insert_into_table();
void list_table_data();
void search_table();
void delete_record();
void delete_table();
void load_tables();
void save_tables();

int main() {
    load_tables(); 

    int option;

    while (1) {
        printf("\n--- SGBD ITP ---\n");
        printf("1. Criar Tabela\n");
        printf("2. Listar Todas as Tabelas\n");
        printf("3. Inserir Nova Linha\n");
        printf("4. Listar Dados de uma Tabela\n");
        printf("5. Pesquisar em uma Tabela\n");
        printf("6. Apagar uma Tupla\n");
        printf("7. Apagar uma Tabela\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1: create_table(); break;
            case 2: list_tables(); break;
            case 3: insert_into_table(); break;
            case 4: list_table_data(); break;
            case 5: search_table(); break;
            case 6: delete_record(); break;
            case 7: delete_table(); break;
            case 8: save_tables(); exit(0); 
            default: printf("Opção inválida!\n");
        }
    }

    return 0;
}

void create_table() {
    if (num_tables >= MAX_TABLES) {
        printf("Limite de tabelas atingido.\n");
        return;
    }

    Table new_table;
    printf("Digite o nome da tabela: ");
    scanf("%s", new_table.name);

    printf("Quantas colunas a tabela terá? ");
    scanf("%d", &new_table.num_columns);

    int primary_key_found = 0;
    for (int i = 0; i < new_table.num_columns; i++) {
        printf("Nome da coluna %d: ", i + 1);
        scanf("%s", new_table.columns[i].name);
        printf("Tipo da coluna %d (char, int, float, double, string): ", i + 1);
        scanf("%s", new_table.columns[i].type);

        if (strcmp(new_table.columns[i].type, "int") == 0) {
            primary_key_found = 1;
        }
    }

    printf("Digite o nome da coluna que será a chave primária: ");
    scanf("%s", new_table.primary_key);


    int primary_key_valid = 0;
    for (int i = 0; i < new_table.num_columns; i++) {
        if (strcmp(new_table.columns[i].name, new_table.primary_key) == 0 &&
            strcmp(new_table.columns[i].type, "int") == 0) {
            primary_key_valid = 1;
            break;
        }
    }

    if (!primary_key_valid) {
        printf("Erro: A chave primária deve ser uma coluna existente e do tipo int.\n");
        return;
    }


    tables[num_tables++] = new_table;
    save_tables();

    FILE *file = fopen(new_table.name, "w"); 
    if (file) {
        fclose(file);
    }

    printf("Tabela criada com sucesso!\n");
}

void list_tables() {
    if (num_tables == 0) {
        printf("Nenhuma tabela encontrada.\n");
        return;
    }

    printf("\nTabelas disponíveis:\n");
    for (int i = 0; i < num_tables; i++) {
        printf("%s\n", tables[i].name);
    }
}

void insert_into_table() {
    char table_name[MAX_NAME_LENGTH];
    printf("Digite o nome da tabela onde deseja inserir um registro: ");
    scanf("%s", table_name);

    Table *table = NULL;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table = &tables[i];
            break;
        }
    }

    if (!table) {
        printf("Tabela não encontrada.\n");
        return;
    }

    Record new_record;
    for (int i = 0; i < table->num_columns; i++) {
        printf("Digite o valor para a coluna %s: ", table->columns[i].name);
        scanf("%s", new_record.values[i]);

        if (strcmp(table->columns[i].name, table->primary_key) == 0) {

            FILE *file = fopen(table_name, "r");
            if (file) {
                Record existing_record;
                while (fscanf(file, "%s", existing_record.values[i]) != EOF) {
                    if (strcmp(existing_record.values[i], new_record.values[i]) == 0) {
                        printf("Erro: Chave primária duplicada.\n");
                        fclose(file);
                        return;
                    }
                }
                fclose(file);
            }
        }
    }


    FILE *file = fopen(table_name, "a");
    if (file) {
        for (int i = 0; i < table->num_columns; i++) {
            fprintf(file, "%s ", new_record.values[i]);
        }
        fprintf(file, "\n");
        fclose(file);
        printf("Registro inserido com sucesso!\n");
    }
}

void list_table_data() {
    char table_name[MAX_NAME_LENGTH];
    printf("Digite o nome da tabela para listar os dados: ");
    scanf("%s", table_name);

    Table *table = NULL;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table = &tables[i];
            break;
        }
    }

    if (!table) {
        printf("Tabela não encontrada.\n");
        return;
    }

    FILE *file = fopen(table_name, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo da tabela.\n");
        return;
    }

    Record record;
    while (1) {
        int read_count = 0;
        for (int i = 0; i < table->num_columns; i++) {
            read_count += fscanf(file, "%s", record.values[i]);
        }
        if (read_count != table->num_columns) {
            break; 
        }

        for (int i = 0; i < table->num_columns; i++) {
            printf("%s: %s ", table->columns[i].name, record.values[i]);
        }
        printf("\n");
    }

    fclose(file);
}

void search_table() {
    char table_name[MAX_NAME_LENGTH];
    printf("Digite o nome da tabela para realizar a pesquisa: ");
    scanf("%s", table_name);

    Table *table = NULL;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table = &tables[i];
            break;
        }
    }

    if (!table) {
        printf("Tabela não encontrada.\n");
        return;
    }

    printf("Escolha uma coluna para pesquisa:\n");
    for (int i = 0; i < table->num_columns; i++) {
        printf("%d. %s\n", i + 1, table->columns[i].name);
    }
    int column_choice;
    scanf("%d", &column_choice);
    column_choice--;

    if (column_choice < 0 || column_choice >= table->num_columns) {
        printf("Coluna inválida.\n");
        return;
    }

    char search_value[MAX_NAME_LENGTH];
    printf("Digite o valor para pesquisa: ");
    scanf("%s", search_value);

    FILE *file = fopen(table_name, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo da tabela.\n");
        return;
    }

    Record record;
    while (!feof(file)) {
        for (int i = 0; i < table->num_columns; i++) {
            fscanf(file, "%s", record.values[i]);
        }
        if (strcmp(record.values[column_choice], search_value) == 0) {
            for (int i = 0; i < table->num_columns; i++) {
                printf("%s: %s ", table->columns[i].name, record.values[i]);
            }
            printf("\n");
        }
    }
    fclose(file);
}

void delete_record() {
    char table_name[MAX_NAME_LENGTH];
    printf("Digite o nome da tabela para apagar um registro: ");
    scanf("%s", table_name);

    Table *table = NULL;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table = &tables[i];
            break;
        }
    }

    if (!table) {
        printf("Tabela não encontrada.\n");
        return;
    }

    char primary_key_value[MAX_NAME_LENGTH];
    printf("Digite o valor da chave primária do registro a ser apagado: ");
    scanf("%s", primary_key_value);

    FILE *file = fopen(table_name, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo da tabela.\n");
        return;
    }

    FILE *temp_file = fopen("temp.dat", "w");
    if (!temp_file) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(file);
        return;
    }

    Record record;
    int record_deleted = 0;

    while (1) {
        int read_count = 0;
        for (int i = 0; i < table->num_columns; i++) {
            read_count += fscanf(file, "%s", record.values[i]);
        }
        if (read_count != table->num_columns) {
            break; 
        }

        if (strcmp(record.values[0], primary_key_value) != 0) {
            for (int i = 0; i < table->num_columns; i++) {
                fprintf(temp_file, "%s ", record.values[i]);
            }
            fprintf(temp_file, "\n");
        } else {
            record_deleted = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(table_name);               
    rename("temp.dat", table_name);   

    if (record_deleted) {
        printf("Registro apagado com sucesso!\n");
    } else {
        printf("Registro não encontrado.\n");
    }
}

void delete_table() {
    char table_name[MAX_NAME_LENGTH];
    printf("Digite o nome da tabela a ser apagada: ");
    scanf("%s", table_name);

    int table_index = -1;
    for (int i = 0; i < num_tables; i++) {
        if (strcmp(tables[i].name, table_name) == 0) {
            table_index = i;
            break;
        }
    }

    if (table_index == -1) {
        printf("Tabela não encontrada.\n");
        return;
    }

    remove(table_name);

    for (int i = table_index; i < num_tables - 1; i++) {
        tables[i] = tables[i + 1];
    }
    num_tables--;

    save_tables(); 
    printf("Tabela apagada com sucesso!\n");
}

void load_tables() {
    FILE *file = fopen(TABLES_FILE, "r");
    if (file) {
        fscanf(file, "%d", &num_tables);
        for (int i = 0; i < num_tables; i++) {
            fscanf(file, "%s %d %s", tables[i].name, &tables[i].num_columns, tables[i].primary_key);
            for (int j = 0; j < tables[i].num_columns; j++) {
                fscanf(file, "%s %s", tables[i].columns[j].name, tables[i].columns[j].type);
            }
        }
        fclose(file);
    }
}

void save_tables() {
    FILE *file = fopen(TABLES_FILE, "w");
    if (file) {
        fprintf(file, "%d\n", num_tables);
        for (int i = 0; i < num_tables; i++) {
            fprintf(file, "%s %d %s\n", tables[i].name, tables[i].num_columns, tables[i].primary_key);
            for (int j = 0; j < tables[i].num_columns; j++) {
                fprintf(file, "%s %s\n", tables[i].columns[j].name, tables[i].columns[j].type);
            }
        }
        fclose(file);
    }
}
