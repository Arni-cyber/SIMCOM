#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Lê uma linha de entrada de forma segura.
 * @param buffer Buffer de destino.
 * @param size Tamanho máximo do buffer.
 */
static void read_safe_line(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) != NULL) {
        // Remove o newline (\n) se estiver presente
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

void read_contact_interactive(Contact *c) {
    printf("\n--- Adicionar Novo Contato ---\n");
    
    // Leitura do Nome
    printf("Nome (max %d): ", NAME_MAX - 1);
    read_safe_line(c->name, NAME_MAX);

    // Leitura do Email
    printf("Email (max %d): ", EMAIL_MAX - 1);
    read_safe_line(c->email, EMAIL_MAX);

    // Leitura da Idade
    printf("Idade (0-255): ");
    char age_str[10];
    read_safe_line(age_str, 10);
    // Conversão de string para uint8_t (simples, sem validação robusta por agora)
    c->age = (uint8_t)atoi(age_str); 
    
    // O ID será gerado no 'add_contact'
}