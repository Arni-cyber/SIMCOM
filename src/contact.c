#include "contact.h"
#include <stdio.h>
#include <stdlib.h> // Para realloc [cite: 9]
#include <string.h> // Para strcmp, memcpy

// Variável estática para gerenciar o próximo ID
static uint32_t next_id = 1;

// --- Implementação do CRUD em Memória ---

int add_contact(Contact **list, size_t *count, const Contact *new_contact) {
    // 1. Alocação dinâmica com realloc para aumentar o vetor [cite: 9]
    size_t new_count = *count + 1;
    Contact *new_list = realloc(*list, new_count * sizeof(Contact));

    // 2. Tratar falha de alocação (ponteiro nulo) [cite: 13, 69]
    if (new_list == NULL) {
        fprintf(stderr, "Erro de alocação de memória ao adicionar contato.\n");
        return -1;
    }

    // 3. Atualiza a lista e o contador
    *list = new_list;
    (*count)++;

    // 4. Copia o novo contato para a última posição e atribui ID
    // O ID é atribuído aqui no momento da adição em memória.
    Contact *c = &(*list)[new_count - 1];
    *c = *new_contact;
    c->id = next_id++; // Atribui o ID e incrementa

    return 0;
}

void list_contacts(const Contact *list, size_t count) {
    printf("--- Lista de Contatos (%zu) ---\n", count);
    if (count == 0) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    // Cabeçalho da tabela
    printf("%-5s | %-30s | %-30s | %-4s\n", "ID", "Nome", "Email", "Idade");
    printf("--------------------------------------------------------------------------------\n");

    // Imprime cada contato
    for (size_t i = 0; i < count; i++) {
        printf("%-5u | %-30s | %-30s | %-4u\n", 
               list[i].id, 
               list[i].name, 
               list[i].email, 
               list[i].age);
    }
    printf("--------------------------------------------------------------------------------\n");
}

// --- Funções de Comparação para qsort ---

// Compara contatos por nome (para qsort) [cite: 12, 34]
int cmp_by_name(const void *a, const void *b) {
    const Contact *contact_a = (const Contact *)a;
    const Contact *contact_b = (const Contact *)b;
    return strcmp(contact_a->name, contact_b->name);
}

// Compara contatos por email (para qsort) [cite: 12, 34]
int cmp_by_email(const void *a, const void *b) {
    const Contact *contact_a = (const Contact *)a;
    const Contact *contact_b = (const Contact *)b;
    return strcmp(contact_a->email, contact_b->email);
}