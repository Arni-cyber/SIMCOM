#include "contato.h"
#include <stdio.h>
#include <stdlib.h> // Para realloc
#include <string.h> // Para strcmp, memcpy

// Variável estática para gerenciar o próximo ID
static uint32_t proximo_id = 1;

// --- Implementação do CRUD em Memória ---

int adicionar_contato(Contato **lista, size_t *contador, const Contato *novo_contato) {
    // 1. Alocação dinâmica com realloc para aumentar o vetor
    size_t novo_contador = *contador + 1;
    Contato *nova_lista = realloc(*lista, novo_contador * sizeof(Contato));

    // 2. Tratar falha de alocação (ponteiro nulo)
    if (nova_lista == NULL) {
        fprintf(stderr, "Erro de alocação de memória ao adicionar contato.\n");
        return -1;
    }

    // 3. Atualiza a lista e o contador
    *lista = nova_lista;
    (*contador)++;

    // 4. Copia o novo contato para a última posição e atribui ID
    Contato *c = &(*lista)[novo_contador - 1];
    *c = *novo_contato;
    c->id = proximo_id++; // Atribui o ID e incrementa

    return 0;
}

void listar_contatos(const Contato *lista, size_t contador) {
    printf("--- Lista de Contatos (%zu) ---\n", contador);
    if (contador == 0) {
        printf("Nenhum contato encontrado.\n");
        return;
    }

    // Cabecalho da tabela
    printf("%-5s | %-30s | %-30s | %-4s\n", "ID", "Nome", "Email", "Idade");
    printf("--------------------------------------------------------------------------------\n");

    // Imprime cada contato
    for (size_t i = 0; i < contador; i++) {
        printf("%-5u | %-30s | %-30s | %-4u\n", 
               lista[i].id, 
               lista[i].nome, 
               lista[i].email, 
               lista[i].idade);
    }
    printf("--------------------------------------------------------------------------------\n");
}

// --- Funções de Comparação para qsort ---

// Compara contatos por nome (para qsort)
int comparar_por_nome(const void *a, const void *b) {
    const Contato *contato_a = (const Contato *)a;
    const Contato *contato_b = (const Contato *)b;
    return strcmp(contato_a->nome, contato_b->nome);
}

// Compara contatos por email (para qsort)
int comparar_por_email(const void *a, const void *b) {
    const Contato *contato_a = (const Contato *)a;
    const Contato *contato_b = (const Contato *)b;
    return strcmp(contato_a->email, contato_b->email);
}
