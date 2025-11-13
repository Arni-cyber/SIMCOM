#ifndef STORAGE_H
#define STORAGE_H

#include <stddef.h> // Para size_t
#include "contact.h" // Depende da definição da struct Contact

/**
 * @brief Carrega os contatos de um arquivo binário para a memória.
 * * Descobre o tamanho do arquivo, calcula o número de structs Contact,
 * e aloca memória dinamicamente antes de ler os dados.
 * * @param filename Nome do arquivo binário (ex: "data/contacts.bin").
 * @param list Ponteiro para o ponteiro da lista de contatos (Contact**), que será alocado.
 * @param count Ponteiro para o contador de contatos (size_t*), que será atualizado.
 * @return 0 em sucesso, -1 em falha (exceto arquivo não existente).
 */
int load_contacts(const char *filename, Contact **list, size_t *count);

/**
 * @brief Salva todos os contatos da memória para um arquivo binário.
 * * Abre o arquivo no modo de escrita binária ("wb") e usa fwrite.
 * * @param filename Nome do arquivo binário (ex: "data/contacts.bin").
 * @param list Lista de contatos a ser salva.
 * @param count Número de contatos na lista.
 * @return 0 em sucesso, -1 em falha.
 */
int save_contacts(const char *filename, const Contact *list, size_t count);

// Protótipo para a função de remoção que precisará atualizar o arquivo
// int remove_contact_by_id(const char *filename, uint32_t id); // Sugestão

#endif // STORAGE_H