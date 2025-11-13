#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "contato.h"

// --- Funções Utilitárias ---

/**
 * @brief Leitura interativa e segura de dados de contato do usuário.
 * @param c Ponteiro para a struct Contato onde os dados serão salvos.
 */
void ler_contato_interativo(Contato *c);

#endif // UTILIDADES_H
