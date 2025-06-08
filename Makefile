# Nome do executável
TARGET = bin/main

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude -lm

# Diretórios
SRCDIR = src
INCDIR = include
BINDIR = bin

# Arquivos fonte
SOURCES := $(wildcard $(SRCDIR)/*.c)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(SOURCES) | $(BINDIR)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "Compilado com sucesso"
# Criar diretório bin se não existir
$(BINDIR):
	@mkdir -p $(BINDIR)

# Limpar arquivos compilados
clean:
	@rm -f $(TARGET)

# Executar o programa
run: all
	@./$(TARGET)

.PHONY: all clean run o que vc criou para mim esta parecido com esse?