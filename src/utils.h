#ifndef UTILS_H
#define UTILS_H

#include "contact.h"

// --- Funções Utilitárias ---

/**
 * @brief Leitura interativa e segura de dados de contato do usuário.
 * @param c Ponteiro para a struct Contact onde os dados serão salvos.
 */
void read_contact_interactive(Contact *c);

// Você pode adicionar mais utilitários aqui, como um para parsing de linha de comando
// (que poderia ficar no main.c ou em um arquivo separado).

#endif // UTILS_H