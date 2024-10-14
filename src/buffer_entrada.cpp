#include "../include/buffer_entrada.h"
#include "../include/big_file.h"
#include <cstdlib>
#include <cstdio> 
#include <cstring>

BufferEntrada::BufferEntrada(const char* nome_arquivo, int tamanho_buffer)
    : tamanho_buffer(tamanho_buffer), posicao_atual(0), registros_restantes(0) {
    
    buffer = (ITEM_VENDA*) malloc(tamanho_buffer * sizeof(ITEM_VENDA));
    if (buffer == nullptr) {
        perror("Erro ao alocar memória para o buffer");
        exit(EXIT_FAILURE);
    }

    arquivo = fopen(nome_arquivo, "rb");  // Usando fopen para abrir o arquivo
    if (arquivo == nullptr) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    // Carrega o buffer inicial
    carregar();
}

BufferEntrada::~BufferEntrada() {
    if (arquivo != nullptr) {
        fclose(arquivo);  // Usando fclose para fechar o arquivo
    }
    free(buffer);
}

void BufferEntrada::carregar() {
    registros_restantes = fread(buffer, sizeof(ITEM_VENDA), tamanho_buffer, arquivo);  // Usando fread para ler o arquivo
    posicao_atual = 0;
}

ITEM_VENDA BufferEntrada::proximo() {
    if (vazio()) {
        carregar();  // Recarrega o buffer se estiver vazio
    }

    return buffer[posicao_atual++];
}

bool BufferEntrada::vazio() const {
    return posicao_atual >= registros_restantes;
}