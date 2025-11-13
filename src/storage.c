#include "storage.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc
#include <string.h> // Para memcpy

// O nome do arquivo binário que você está usando (conforme o documento)
#define CONTACTS_FILE "data/contacts.bin"

// Variável estática para manter o controle do maior ID carregado
static uint32_t max_id_loaded = 0;

int load_contacts(const char *filename, Contact **list, size_t *count) {
    FILE *file = fopen(filename, "rb"); // Abrir em modo binário de leitura [cite: 71]

    // 1. Tratamento: Arquivo não existe ou não pode ser aberto
    if (file == NULL) {
        // Se o arquivo não existe, é normal. Apenas começamos com lista vazia.
        *list = NULL;
        *count = 0;
        return 0; 
    }

    // 2. Descobrir o tamanho do arquivo para alocação
    // fseek vai para o fim do arquivo
    fseek(file, 0, SEEK_END);
    // ftell retorna a posição atual (tamanho em bytes)
    long file_size = ftell(file);
    // fseek volta para o início para começar a leitura
    fseek(file, 0, SEEK_SET);

    // 3. Calcular o número de contatos e alocar
    size_t num_contacts = 0;
    if (file_size > 0) {
        // Cálculo conforme a observação[cite: 68]: n = size / sizeof(Contact)
        size_t contact_size = sizeof(Contact);
        num_contacts = file_size / contact_size;
        
        // Alocar a memória necessária: malloc(n * sizeof(Contact)) [cite: 68]
        *list = (Contact *)malloc(num_contacts * contact_size);

        // Tratar ponteiro nulo após malloc [cite: 69]
        if (*list == NULL) {
            fprintf(stderr, "Erro de alocação de memória ao carregar contatos.\n");
            fclose(file);
            return -1;
        }

        // 4. Ler os dados do arquivo para a memória
        size_t items_read = fread(*list, contact_size, num_contacts, file);

        // Tratar erro de I/O (fread retornos) [cite: 69]
        if (items_read != num_contacts) {
            fprintf(stderr, "Erro de leitura: apenas %zu de %zu contatos lidos.\n", items_read, num_contacts);
            free(*list);
            *list = NULL;
            *count = 0;
            fclose(file);
            return -1;
        }
    } else {
        // Arquivo vazio
        *list = NULL;
    }
    
    fclose(file);

    // 5. Atualizar o contador e o maior ID
    *count = num_contacts;
    if (num_contacts > 0) {
        // É importante recalcular o 'next_id' (em contact.c) para evitar IDs duplicados.
        // O ID é o último elemento do vetor que está ordenado por ID. 
        // Para simplificar, o projeto exige que você garanta que o ID seja único[cite: 26].
        // Vamos percorrer a lista para encontrar o ID mais alto.
        max_id_loaded = 0;
        for (size_t i = 0; i < num_contacts; i++) {
            if ((*list)[i].id > max_id_loaded) {
                max_id_loaded = (*list)[i].id;
            }
        }
    }
    // NOTA: É necessário um mecanismo em 'contact.c' para que o 'next_id' comece em max_id_loaded + 1.

    return 0;
}

int save_contacts(const char *filename, const Contact *list, size_t count) {
    // Abrir em modo binário de escrita ("wb") para sobrescrever o arquivo [cite: 71, 100]
    FILE *file = fopen(filename, "wb"); 

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar: %s\n", filename);
        return -1;
    }

    // Escrever todo o vetor de contatos de uma vez [cite: 100]
    size_t items_written = fwrite(list, sizeof(Contact), count, file);

    // Tratar erro de I/O
    if (items_written != count) {
        fprintf(stderr, "Erro de escrita: apenas %zu de %zu contatos foram salvos.\n", items_written, count);
        fclose(file);
        // Não liberamos 'list' aqui pois a memória pertence ao 'main.c'
        return -1;
    }

    fclose(file);
    return 0;
}