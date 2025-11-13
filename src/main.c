#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "utils.h"
// Adicionar include para storage.h/storage.c quando criados

// --- Protótipos das funções de Storage (a serem implementadas em storage.c) ---
// Usaremos estes protótipos para que o main.c compile por agora.
int load_contacts(const char *filename, Contact **list, size_t *count);
int save_contacts(const char *filename, const Contact *list, size_t count);

// --- Loop Principal e Parsing de Comandos ---

int main(int argc, char *argv[]) {
    // A lista de contatos será carregada do arquivo [cite: 41, 42]
    Contact *list = NULL; 
    size_t count = 0;

    // 1. Tenta carregar contatos do arquivo binário [cite: 43]
    if (load_contacts("data/contacts.bin", &list, &count) != 0) {
        fprintf(stderr, "Aviso: Falha ao carregar contatos, iniciando com lista vazia.\n");
        // Não é um erro fatal, o arquivo pode não existir ainda.
    }

    // 2. Parsing de linha de comando simples (subcomandos) [cite: 46, 47]
    if (argc >= 2) {
        const char *subcommand = argv[1];

        if (strcmp(subcommand, "add") == 0) {
            // Comando: ./simcon add [cite: 33, 82]
            Contact c = {0}; // Inicializa struct [cite: 49]
            read_contact_interactive(&c); // Lê dados do usuário [cite: 50]
            
            if (add_contact(&list, &count, &c) == 0) { // Adiciona em memória [cite: 51]
                // Salva imediatamente no arquivo [cite: 33, 52]
                if (save_contacts("data/contacts.bin", list, count) == 0) {
                    printf("Contato adicionado e salvo com sucesso! (ID: %u)\n", c.id);
                }
            }

        } else if (strcmp(subcommand, "list") == 0) {
            // Comando: ./simcon list [--sort name|email] [cite: 34, 83]
            int (*cmp_func)(const void*, const void*) = cmp_by_name; // Padrão: nome [cite: 55]
            
            // Verifica se a opção de ordenação foi passada
            if (argc >= 3 && strcmp(argv[2], "--sort") == 0 && argc >= 4) {
                if (strcmp(argv[3], "email") == 0) {
                    cmp_func = cmp_by_email; // Usa ponteiro para função de email
                    printf("Ordenando por Email...\n");
                } else if (strcmp(argv[3], "name") == 0) {
                    // Já é o padrão, mas pode ser explícito
                    printf("Ordenando por Nome...\n");
                }
            }

            // Ordena o vetor (qsort usa ponteiro para função) [cite: 56, 57]
            qsort(list, count, sizeof(Contact), cmp_func); 
            list_contacts(list, count); // Lista os resultados [cite: 58]

        } else {
            // Outros subcomandos (find, remove, export) [cite: 60]
            fprintf(stderr, "Comando desconhecido: %s\n", subcommand);
        }

    } else {
        // Sem argumentos: modo de uso simples
        printf("SIMCON - Sistema de Gerenciamento de Contatos\n");
        printf("Uso: ./simcon <add|list|find|remove|export>\n");
        printf("Tente: ./simcon list\n");
    }

    // 3. Libera a memória alocada dinamicamente [cite: 9, 64]
    free(list);

    return 0; // [cite: 65]
}

// --- Implementação Stubs para Storage (Temporário, substituir por storage.c) ---

// Carregar contatos (stub: simula lista vazia)
int load_contacts(const char *filename, Contact **list, size_t *count) {
    // A implementação real usará fopen, fseek/ftell, malloc e fread [cite: 68, 99]
    FILE *file = fopen(filename, "rb"); // Abrir em modo binário de leitura [cite: 71]
    if (file == NULL) {
        // Isso é comum se o arquivo não existe. Retornar 1 para indicar 'falha', mas não fatal.
        return 1;
    }
    
    // Simulação: se o arquivo existe, ele está vazio por enquanto.
    // Lógica real: determinar o tamanho do arquivo, calcular 'n' e ler os dados.
    fclose(file);
    return 0;
}

// Salvar contatos (stub: simula sucesso)
int save_contacts(const char *filename, const Contact *list, size_t count) {
    // A implementação real usará fopen e fwrite [cite: 100]
    FILE *file = fopen(filename, "wb"); // Abrir em modo binário de escrita (sobrescreve) [cite: 71]
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar: %s\n", filename);
        return -1;
    }
    
    // Lógica real:
    // fwrite(list, sizeof(Contact), count, file);
    
    printf("Salvando %zu contatos em %s...\n", count, filename);
    fclose(file);
    return 0;
}