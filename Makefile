# Definições de variáveis
CXX = g++
CXXFLAGS = -std=c++17 -g -Iinclude
LDFLAGS =
OBJDIR = obj
SRCDIR = src
INCDIR = include
BINDIR = bin
DATADIR = data

# Lista de arquivos fonte e objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXECUTABLES = $(BINDIR)/gerar_arquivo $(BINDIR)/ordenacao_externa $(BINDIR)/main

# Regra padrão
all: $(EXECUTABLES)

# Regras para criar o diretório de objetos e binários
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Regras para compilar os arquivos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regras para compilar o main
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $@

# Regras para linkar os executáveis
$(BINDIR)/gerar_arquivo: $(OBJDIR)/gerar_arquivo.o $(OBJDIR)/big_file.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR)/ordenacao_externa: $(OBJDIR)/main.o $(OBJDIR)/ordenacao_externa.o $(OBJDIR)/buffer_entrada.o $(OBJDIR)/buffer_saida.o $(OBJDIR)/big_file.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR)/main: $(OBJDIR)/main.o $(OBJDIR)/big_file.o $(OBJDIR)/ordenacao_externa.o $(OBJDIR)/buffer_entrada.o $(OBJDIR)/buffer_saida.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/*

# Para evitar que o diretório bin seja removido
.PHONY: all clean
