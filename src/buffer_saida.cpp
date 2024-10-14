#include "../include/buffer_saida.h"
#include <cstdio>
#include <cstdlib>

BufferSaida::BufferSaida(const char* nome_arquivo, int tamanho_buffer)
    : tamanho_buffer(tamanho_buffer), posicao_atual(0) {
    buffer = (ITEM_VENDA*) malloc(sizeof(ITEM_VENDA) * tamanho_buffer);
    if (buffer == nullptr) {
        perror("Erro ao alocar memória para o buffer de saída");
        exit(EXIT_FAILURE);
    }

    arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == nullptr) {
        perror("Erro ao abrir o arquivo de saída");
        free(buffer);
        exit(EXIT_FAILURE);
    }
}

BufferSaida::~BufferSaida() {
    despejar(); // Despeja o restante dos registros
    fclose(arquivo);
    free(buffer);
}

void BufferSaida::inserir(const ITEM_VENDA& registro) {
    if (posicao_atual >= tamanho_buffer) {
        despejar(); // Despeja o buffer quando estiver cheio
    }
    buffer[posicao_atual++] = registro;
}

void BufferSaida::despejar() {
    if (posicao_atual > 0) {
        fwrite(buffer, sizeof(ITEM_VENDA), posicao_atual, arquivo);
        posicao_atual = 0;
    }
}
