#ifndef ARMAZENAMENTO_H
#define ARMAZENAMENTO_H

#include <stddef.h> 
#include "contato.h" 

//  Funções de Persistência

/*
  Carrega os contatos de um arquivo binário para a memória.
  nome_arquivo Nome do arquivo binário (ex: "data/contatos.bin").
  lista Ponteiro para o ponteiro da lista de contatos (Contato**).
  contador Ponteiro para o contador de contatos (size_t*).
 */
int carregar_contatos(const char *nome_arquivo, Contato **lista, size_t *contador);

/*
  Salva todos os contatos da memória para um arquivo binário.
  nome_arquivo Nome do arquivo binário (ex: "data/contatos.bin").
  lista Lista de contatos a ser salva.
  contador Número de contatos na lista.
 */
int salvar_contatos(const char *nome_arquivo, const Contato *lista, size_t contador);

#endif // ARMAZENAMENTO_H

/*
  Exporta a lista de contatos para um arquivo texto ou CSV.
  nome_arquivo O nome do arquivo de saida.
  formato O formato de exportacao ("texto" ou "csv").
  lista Lista de contatos.
  contador Numero de contatos.
 */

int exportar_contatos(const char *nome_arquivo, const char *formato, 
                      const Contato *lista, size_t contador);

#endif // ARMAZENAMENTO_H


