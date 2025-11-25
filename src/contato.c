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

// --- Funções de Comparação para pesquisa ---

// Compara contatos por nome (para pesquisa)
int comparar_por_nome(const void *a, const void *b) {
    const Contato *contato_a = (const Contato *)a;
    const Contato *contato_b = (const Contato *)b;
    return strcmp(contato_a->nome, contato_b->nome);
}

// Compara contatos por email (para pesquisa)
int comparar_por_email(const void *a, const void *b) {
    const Contato *contato_a = (const Contato *)a;
    const Contato *contato_b = (const Contato *)b;
    return strcmp(contato_a->email, contato_b->email);
}

// --- Funções de Busca ---

/**
 * @brief Função de callback para buscar por substring no nome.
 * @param contato O contato a ser verificado.
 * @param consulta A substring a ser buscada.
 * @return 1 se a substring for encontrada, 0 caso contrario.
 */
int busca_por_nome_cb(const Contato *contato, const char *consulta) {
    // strstr retorna NULL se a substring nao for encontrada.
    // strcasestr e melhor, mas nao e padrao C (GNU extension). Usamos strstr por padrao.
    return strstr(contato->nome, consulta) != NULL;
}

/**
 * @brief Função de callback para buscar por substring no email.
 * @param contato O contato a ser verificado.
 * @param consulta A substring a ser buscada.
 * @return 1 se a substring for encontrada, 0 caso contrario.
 */
int busca_por_email_cb(const Contato *contato, const char *consulta) {
    return strstr(contato->email, consulta) != NULL;
}

/**
 * @brief Realiza a busca em memoria usando uma funcao de callback.
 * @param lista Lista completa de contatos.
 * @param contador Numero total de contatos.
 * @param func_busca Ponteiro para a funcao de busca (callback).
 * @param consulta A string de busca.
 * @return Um ponteiro para uma nova lista de resultados (alocada dinamicamente) ou NULL.
 */
Contato *buscar_contatos(const Contato *lista, size_t contador,
                         int (*func_busca)(const Contato*, const char*),
                         const char *consulta, size_t *cont_resultados) {
    
    Contato *resultados = NULL;
    size_t temp_count = 0;

    for (size_t i = 0; i < contador; i++) {
        if (func_busca(&lista[i], consulta)) {
            // Se a busca for positiva, realoca o vetor de resultados e copia o contato
            temp_count++;
            Contato *nova_lista = realloc(resultados, temp_count * sizeof(Contato));

            if (nova_lista == NULL) {
                fprintf(stderr, "Erro de alocação de memória na busca.\n");
                free(resultados);
                *cont_resultados = 0;
                return NULL;
            }

            resultados = nova_lista;
            resultados[temp_count - 1] = lista[i];
        }
    }

    *cont_resultados = temp_count;
    return resultados;
}

// --- Funções de Remoção ---

/**
 * @brief Remove um contato da lista em memoria, usando memmove e realloc.
 * @param lista Ponteiro para a lista de contatos (Contato* *).
 * @param contador Ponteiro para o contador de contatos (size_t *).
 * @param id_remover O ID do contato a ser removido.
 * @return 0 em sucesso, -1 se nao encontrado, -2 se realloc falhar.
 */
int remover_contato_por_id(Contato **lista, size_t *contador, uint32_t id_remover) {
    size_t indice_remover = -1;

    // 1. Encontrar o indice do contato
    for (size_t i = 0; i < *contador; i++) {
        if ((*lista)[i].id == id_remover) {
            indice_remover = i;
            break;
        }
    }

    if (indice_remover == (size_t)-1) {
        return -1; // Contato não encontrado
    }

    // 2. Compactar o vetor usando memmove
    if (indice_remover < (*contador - 1)) {
        // move o bloco de memória que começa apos o item removido (indice_remover + 1)
        // para a posicao do item removido (indice_remover).
        memmove(&(*lista)[indice_remover], 
                &(*lista)[indice_remover + 1], 
                (*contador - indice_remover - 1) * sizeof(Contato));
    }

    // 3. Decrementar o contador
    (*contador)--;

    // 4. Redimensionar/encolher o vetor com realloc
    Contato *nova_lista = realloc(*lista, (*contador) * sizeof(Contato));
    
    // NOTA: Se contador for 0, nova_lista pode ser NULL, o que e correto (lista vazia).
    if (nova_lista == NULL && *contador > 0) {
        // Falha de realloc MANTENDO o item removido, mas a memoria ficou inconsistente.
        return -2;
    }
    
    *lista = nova_lista;

    return 0;
}
