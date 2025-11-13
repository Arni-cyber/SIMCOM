#ifndef ARMAZENAMENTO_H
#define ARMAZENAMENTO_H

#include <stddef.h> 
#include "contato.h" 

// --- Funções de Persistência ---

/**
 * @brief Carrega os contatos de um arquivo binário para a memória.
 * @param nome_arquivo Nome do arquivo binário (ex: "data/contatos.bin").
 * @param lista Ponteiro para o ponteiro da lista de contatos (Contato**).
 * @param contador Ponteiro para o contador de contatos (size_t*).
 * @return 0 em sucesso, -1 em falha.
 */
int carregar_contatos(const char *nome_arquivo, Contato **lista, size_t *contador);

/**
 * @brief Salva todos os contatos da memória para um arquivo binário.
 * @param nome_arquivo Nome do arquivo binário (ex: "data/contatos.bin").
 * @param lista Lista de contatos a ser salva.
 * @param contador Número de contatos na lista.
 * @return 0 em sucesso, -1 em falha.
 */
int salvar_contatos(const char *nome_arquivo, const Contato *lista, size_t contador);

#endif // ARMAZENAMENTO_H
