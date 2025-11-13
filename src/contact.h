#ifndef CONTACT_H
#define CONTACT_H

#include <stdint.h> // Para uint32_t e uint8_t [cite: 31]
#include <stddef.h> // Para size_t

// Definições de tamanho máximo para nome e email [cite: 23, 24]
#define NAME_MAX 64
#define EMAIL_MAX 64

// Estrutura Contact [cite: 25]
typedef struct {
    uint32_t id;      // identificador único [cite: 26]
    char name[NAME_MAX];
    char email[EMAIL_MAX];
    uint8_t age;
} Contact;

// --- Funções de Manipulação em Memória (CRUD) ---

/**
 * @brief Adiciona um novo contato à lista (usando realloc).
 * @param list Ponteiro para a lista de contatos (Contact* *).
 * @param count Ponteiro para o contador de contatos (size_t *).
 * @param new_contact O contato a ser adicionado.
 * @return 0 em sucesso, -1 em falha de alocação.
 */
int add_contact(Contact **list, size_t *count, const Contact *new_contact);

/**
 * @brief Lista todos os contatos.
 * @param list Lista de contatos.
 * @param count Número de contatos.
 */
void list_contacts(const Contact *list, size_t count);

// Declarações de funções de comparação para ponteiros para função (qsort)
int cmp_by_name(const void *a, const void *b);
int cmp_by_email(const void *a, const void *b);

#endif // CONTACT_H