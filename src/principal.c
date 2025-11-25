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


// 2. Parsing de linha de comando
    if (argc >= 2) {
        const char *subcomando = argv[1];

        // ... Comandos ADICIONAR e LISTAR (como no exemplo anterior) ...

        if (strcmp(subcomando, "buscar") == 0 || strcmp(subcomando, "find") == 0) {
            // Comando: ./simcon buscar <consulta> [nome|email]
            if (argc < 3) {
                fprintf(stderr, "Uso: ./simcon buscar <substring> [nome|email]\n");
            } else {
                const char *consulta = argv[2];
                // Padrao: busca por nome (callback)
                int (*func_busca_cb)(const Contato*, const char*) = busca_por_nome_cb; 
                char *campo = "nome";

                // Verifica se o campo de busca foi especificado
                if (argc >= 4) {
                    if (strcmp(argv[3], "email") == 0) {
                        func_busca_cb = busca_por_email_cb;
                        campo = "email";
                    }
                }

                size_t cont_resultados = 0;
                // Executa a busca
                Contato *resultados = buscar_contatos(lista, contador, func_busca_cb, consulta, &cont_resultados);

                printf("--- Resultados da Busca por '%s' em %s (%zu encontrados) ---\n", consulta, campo, cont_resultados);
                listar_contatos(resultados, cont_resultados);
                free(resultados); // Libera o vetor de resultados, mas nao a lista original!
            }

        } else if (strcmp(subcomando, "remover") == 0 || strcmp(subcomando, "remove") == 0) {
            // Comando: ./simcon remover <id>
            if (argc < 3) {
                fprintf(stderr, "Uso: ./simcon remover <ID_do_contato>\n");
            } else {
                uint32_t id_remover = (uint32_t)strtoul(argv[2], NULL, 10);
                
                int resultado = remover_contato_por_id(&lista, &contador, id_remover);

                if (resultado == 0) {
                    // Se remover em memória, salva a lista compactada no arquivo
                    if (salvar_contatos("data/contatos.bin", lista, contador) == 0) {
                         printf("Contato ID %u removido e arquivo atualizado com sucesso!\n", id_remover);
                    }
                } else if (resultado == -1) {
                    fprintf(stderr, "Erro: Contato ID %u não encontrado.\n", id_remover);
                } else if (resultado == -2) {
                    fprintf(stderr, "Erro fatal de alocação de memória ao remover.\n");
                }
            }
            
        } else if (strcmp(subcomando, "exportar") == 0 || strcmp(subcomando, "export") == 0) {
            // Comando: ./simcon exportar <csv|texto> <nome_arquivo>
            if (argc < 4) {
                fprintf(stderr, "Uso: ./simcon exportar <csv|texto> <nome_arquivo.ext>\n");
            } else {
                const char *formato = argv[2];
                const char *nome_arquivo = argv[3];
                
                exportar_contatos(nome_arquivo, formato, lista, contador);
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

