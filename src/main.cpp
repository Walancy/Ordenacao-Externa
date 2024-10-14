#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

// Incluindo o cabeçalho correto para as funções
#include "../include/big_file.h"
#include "../include/ordenacao_externa.h"

int main(int argc, char** argv) {
    if (argc != 1) {
        std::cerr << "Uso: " << argv[0] << std::endl;
        return 1;
    }

    // Define os tamanhos dos arquivos de teste e o tamanho dos buffers
    struct Teste {
        const char* nome_arquivo;
        unsigned int n_registros;
    };

    Teste testes[] = {
        {"data/teste_256000.dat", 256000},
        {"data/teste_512000.dat", 512000},
        {"data/teste_921600.dat", 921600},
        {"data/teste_1572864.dat", 1572864}
    };

    size_t tamanho_buffer = 8388608;   // 8MB
    size_t tamanho_subbuffer = 4194304; // 4MB

    // Ordena arquivos de teste já gerados
    for (const auto& teste : testes) {
        std::cout << "Ordenando arquivo: " << teste.nome_arquivo << std::endl;
        std::string arquivo_saida = std::string(teste.nome_arquivo) + "_sorted.dat";
        ordenacao_externa(teste.nome_arquivo, tamanho_buffer, tamanho_subbuffer, arquivo_saida.c_str());
        std::cout << "Arquivo ordenado gerado: " << arquivo_saida << std::endl;
    }

    return 0;
}
