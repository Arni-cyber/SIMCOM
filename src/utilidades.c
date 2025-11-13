#include "utilidades.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Lê uma linha de entrada de forma segura.
 * @param buffer Buffer de destino.
 * @param tamanho Tamanho máximo do buffer.
 */
static void ler_linha_segura(char *buffer, size_t tamanho) {
    if (fgets(buffer, (int)tamanho, stdin) != NULL) {
        // Remove o newline (\n) se estiver presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

void ler_contato_interativo(Contato *c) {
    printf("\n--- Adicionar Novo Contato ---\n");
    
    // Leitura do Nome
    printf("Nome (max %d): ", NOME_MAX - 1);
    ler_linha_segura(c->nome, NOME_MAX);

    // Leitura do Email
    printf("Email (max %d): ", EMAIL_MAX - 1);
    ler_linha_segura(c->email, EMAIL_MAX);

    // Leitura da Idade
    printf("Idade (0-255): ");
    char idade_str[10];
    ler_linha_segura(idade_str, 10);
    // Conversão de string para uint8_t
    c->idade = (uint8_t)atoi(idade_str); 
}
