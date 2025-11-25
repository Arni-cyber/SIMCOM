#ifndef CONTATO_H
#define CONTATO_H

#include <stdint.h> // Para uint32_t e uint8_t
#include <stddef.h> // Para size_t

// Definições de tamanho máximo
#define NOME_MAX 64
#define EMAIL_MAX 64

// Estrutura Contato
typedef struct {
    uint32_t id;      // identificador unico
    char nome[NOME_MAX];
    char email[EMAIL_MAX];
    uint8_t idade;
} Contato;

// --- Funções de Manipulação em Memória (CRUD) ---

/**
 * @brief Adiciona um novo contato a lista (usando realloc).
 * @param lista Ponteiro para a lista de contatos (Contato* *).
 * @param contador Ponteiro para o contador de contatos (size_t *).
 * @param novo_contato O contato a ser adicionado.
 * @return 0 em sucesso, -1 em falha de alocacao.
 */
int adicionar_contato(Contato **lista, size_t *contador, const Contato *novo_contato);

/**
 * @brief Lista todos os contatos.
 * @param lista Lista de contatos.
 * @param contador Numero de contatos.
 */
void listar_contatos(const Contato *lista, size_t contador);

// Declarações de funções de comparacao para ponteiros para funcao (qsort)
int comparar_por_nome(const void *a, const void *b);
int comparar_por_email(const void *a, const void *b);

#endif // CONTATO_H

// --- Funções de Busca ---
int busca_por_nome_cb(const Contato *contato, const char *consulta);
int busca_por_email_cb(const Contato *contato, const char *consulta);

Contato *buscar_contatos(const Contato *lista, size_t contador,
                         int (*func_busca)(const Contato*, const char*),
                         const char *consulta, size_t *cont_resultados);

// --- Funções de Remoção ---
int remover_contato_por_id(Contato **lista, size_t *contador, uint32_t id_remover);

// (Restante do contato.h)
