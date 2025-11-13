#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contato.h"
#include "utilidades.h"
#include "armazenamento.h" // Inclui as funções de persistência

// --- Loop Principal e Parsing de Comandos ---

int main(int argc, char *argv[]) {
    // A lista de contatos será carregada do arquivo
    Contato *lista = NULL; 
    size_t contador = 0;

    // 1. Tenta carregar contatos do arquivo binário
    if (carregar_contatos("data/contatos.bin", &lista, &contador) != 0) {
        fprintf(stderr, "Aviso: Falha ao carregar contatos, iniciando com lista vazia.\n");
    }

    // 2. Parsing de linha de comando simples (subcomandos)
    if (argc >= 2) {
        const char *subcomando = argv[1];

        if (strcmp(subcomando, "adicionar") == 0 || strcmp(subcomando, "add") == 0) {
            // Comando: ./simcon adicionar
            Contato c = {0}; 
            ler_contato_interativo(&c); 
            
            if (adicionar_contato(&lista, &contador, &c) == 0) { 
                if (salvar_contatos("data/contatos.bin", lista, contador) == 0) {
                    printf("Contato adicionado e salvo com sucesso! (ID: %u)\n", c.id);
                }
            }

        } else if (strcmp(subcomando, "listar") == 0 || strcmp(subcomando, "list") == 0) {
            // Comando: ./simcon listar [--ordenar nome|email]
            int (*func_comparacao)(const void*, const void*) = comparar_por_nome; // Padrão: nome
            
            // Verifica se a opção de ordenação foi passada
            if (argc >= 3 && strcmp(argv[2], "--ordenar") == 0 && argc >= 4) {
                if (strcmp(argv[3], "email") == 0) {
                    func_comparacao = comparar_por_email; 
                    printf("Ordenando por Email...\n");
                } else if (strcmp(argv[3], "nome") == 0) {
                    printf("Ordenando por Nome...\n");
                }
            }

            // Ordena o vetor (qsort usa ponteiro para função)
            qsort(lista, contador, sizeof(Contato), func_comparacao); 
            listar_contatos(lista, contador); 

        } else {
            // Outros subcomandos (buscar, remover, exportar) - *A SER IMPLEMENTADO*
            fprintf(stderr, "Comando desconhecido: %s\n", subcomando);
        }

    } else {
        // Sem argumentos: modo de uso simples
        printf("SIMCON - Sistema de Gerenciamento de Contatos\n");
        printf("Uso: ./simcon <adicionar|listar|buscar|remover|exportar>\n");
        printf("Tente: ./simcon listar\n");
    }

    // 3. Libera a memória alocada dinamicamente
    free(lista);

    return 0; 
}
