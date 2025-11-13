# Makefile para o projeto SIMCON
# Compilador C a ser usado
CC = gcc
# Flags de compilação: -Wall (warnings), -Wextra (mais warnings), -std=c99 (padrão C99)
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável final
TARGET = simcon

# Diretório de código-fonte
SRC_DIR = src
# Diretório de arquivos objeto
OBJ_DIR = obj
# Diretório onde o executável será colocado (raiz do projeto)
BIN_DIR = .

# Lista de todos os arquivos .c no diretório src
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Substitui a extensão .c por .o e muda o diretório de src para obj
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Objetivo principal (default): compilar o projeto
.PHONY: all
all: $(BIN_DIR)/$(TARGET)

# Cria o executável final: depende de todos os objetos
$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Cria o diretório de objetos antes de compilar os objetos, se ele não existir
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)/$(TARGET) $(wildcard data/*.bin)
	@echo "Arquivos temporários e executável limpos."

# Regra para remover apenas o arquivo de dados binário
.PHONY: cleandata
cleandata:
	@rm -f data/contacts.bin
	@echo "Arquivo de dados (contacts.bin) limpo."

# Regra de execução de exemplo
.PHONY: run
run: $(BIN_DIR)/$(TARGET)
	./$(TARGET) list