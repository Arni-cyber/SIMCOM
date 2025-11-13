# Makefile para o projeto SIMCON
# Compilador C a ser usado
CC = gcc
# Flags de compilação: -Wall (avisos), -Wextra (mais avisos), -std=c99 (padrão C99)
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável final
ALVO = simcon

# Diretório de código-fonte
DIR_FONTES = src
# Diretório de arquivos objeto
DIR_OBJETOS = obj
# Diretório onde o executável será colocado (raiz do projeto)
DIR_BIN = .

# Lista de todos os arquivos .c no diretório src
FONTES = $(wildcard $(DIR_FONTES)/*.c)
# Substitui a extensão .c por .o e muda o diretório
OBJETOS = $(patsubst $(DIR_FONTES)/%.c, $(DIR_OBJETOS)/%.o, $(FONTES))

# Objetivo principal (default): compilar o projeto
.PHONY: tudo
tudo: $(DIR_BIN)/$(ALVO)

# Cria o executável final: depende de todos os objetos
$(DIR_BIN)/$(ALVO): $(OBJETOS)
	@mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) $^ -o $@

# Cria o diretório de objetos antes de compilar os objetos
$(DIR_OBJETOS)/%.o: $(DIR_FONTES)/%.c
	@mkdir -p $(DIR_OBJETOS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
.PHONY: limpar
limpar:
	@rm -rf $(DIR_OBJETOS) $(DIR_BIN)/$(ALVO) $(wildcard data/*.bin)
	@echo "Arquivos temporários e executável limpos."

# Regra para limpar apenas o arquivo de dados binário
.PHONY: limpar_dados
limpar_dados:
	@rm -f data/contatos.bin
	@echo "Arquivo de dados (contatos.bin) limpo."

# Regra de execução de exemplo
.PHONY: rodar
rodar: $(DIR_BIN)/$(ALVO)
	./$(ALVO) listar
