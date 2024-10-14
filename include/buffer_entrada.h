#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdint>
#include "big_file.h"

class BufferEntrada {
public:
    BufferEntrada(const char* nome_arquivo, int tamanho_buffer);
    ~BufferEntrada();

    ITEM_VENDA proximo();  
    bool vazio() const;    

private:
    void carregar();       

    FILE* arquivo;         
    ITEM_VENDA* buffer;    
    int tamanho_buffer;    
    int posicao_atual;     
    size_t registros_restantes; 
};
