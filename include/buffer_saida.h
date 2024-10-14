#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include "big_file.h"

class BufferSaida {
public:
    BufferSaida(const char* nome_arquivo, int tamanho_buffer);
    ~BufferSaida();

    void inserir(const ITEM_VENDA& registro); 
    void despejar();                         

private:
    FILE* arquivo;         
    ITEM_VENDA* buffer;    
    int tamanho_buffer;    
    int posicao_atual;     
};
