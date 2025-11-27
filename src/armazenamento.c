#include "armazenamento.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

int carregar_contatos(const char *nome_arquivo, Contato **lista, size_t *contador) {
    FILE *arquivo = fopen(nome_arquivo, "rb"); // Abrir em modo binário de leitura

    if (arquivo == NULL) {
        *lista = NULL;
        *contador = 0;
        return 0; // Não é um erro fatal se o arquivo não existe
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    size_t num_contatos = 0;
    if (tamanho_arquivo > 0) {
        size_t tamanho_contato = sizeof(Contato);
        num_contatos = tamanho_arquivo / tamanho_contato;
        
        *lista = (Contato *)malloc(num_contatos * tamanho_contato);

        if (*lista == NULL) {
            fprintf(stderr, "Erro de alocação de memória ao carregar contatos.\n");
            fclose(arquivo);
            return -1;
        }

        size_t itens_lidos = fread(*lista, tamanho_contato, num_contatos, arquivo);

        if (itens_lidos != num_contatos) {
            fprintf(stderr, "Erro de leitura: apenas %zu de %zu contatos lidos.\n", itens_lidos, num_contatos);
            free(*lista);
            *lista = NULL;
            *contador = 0;
            fclose(arquivo);
            return -1;
        }
    } else {
        *lista = NULL;
    }
    
    fclose(arquivo);

    *contador = num_contatos;

    return 0;
}

int salvar_contatos(const char *nome_arquivo, const Contato *lista, size_t contador) {
    FILE *arquivo = fopen(nome_arquivo, "wb"); // Abrir em modo binário de escrita (sobrescreve)

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar: %s\n", nome_arquivo);
        return -1;
    }

    size_t itens_escritos = fwrite(lista, sizeof(Contato), contador, arquivo);

    if (itens_escritos != contador) {
        fprintf(stderr, "Erro de escrita: apenas %zu de %zu contatos foram salvos.\n", itens_escritos, contador);
        fclose(arquivo);
        return -1;
    }

    printf("Salvando %zu contatos em %s...\n", contador, nome_arquivo);
    fclose(arquivo);
    return 0;
}


int exportar_contatos(const char *nome_arquivo, const char *formato, 
                      const Contato *lista, size_t contador) {
    
    FILE *arquivo = fopen(nome_arquivo, "w"); // Modo escrita de texto 'w'

    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para exportar: %s\n", nome_arquivo);
        return -1;
    }

    if (strcmp(formato, "csv") == 0) {
        // Cabeçalho CSV
        fprintf(arquivo, "ID,Nome,Email,Idade\n");
        // Corpo CSV
        for (size_t i = 0; i < contador; i++) {
            fprintf(arquivo, "%u,\"%s\",\"%s\",%u\n", 
                    lista[i].id, lista[i].nome, lista[i].email, lista[i].idade);
        }
    } else if (strcmp(formato, "texto") == 0) {
        
        // Formato de texto simples
        fprintf(arquivo, "--- Relatório de Contatos ---\n");
        for (size_t i = 0; i < contador; i++) {
            fprintf(arquivo, "ID: %u | Nome: %s | Email: %s | Idade: %u\n", 
                    lista[i].id, lista[i].nome, lista[i].email, lista[i].idade);
        }
    } else {
        fprintf(stderr, "Formato de exportação desconhecido: %s\n", formato);
        fclose(arquivo);
        return -1;
    }

    printf("Exportação concluída para o arquivo: %s\n", nome_arquivo);
    fclose(arquivo);
    return 0;
}

