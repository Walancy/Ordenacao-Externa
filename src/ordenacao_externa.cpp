#include "../include/ordenacao_externa.h"
#include "../include/buffer_entrada.h"
#include "../include/buffer_saida.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <chrono> // Inclua esta biblioteca para medir o tempo

void intercalacao_k_vias(std::vector<BufferEntrada*>& buffers, BufferSaida& buffer_saida) {
    auto comparar = [](const std::pair<ITEM_VENDA, int>& a, const std::pair<ITEM_VENDA, int>& b) {
        return a.first.id > b.first.id;
    };
    std::vector<std::pair<ITEM_VENDA, int>> heap;

    for (size_t i = 0; i < buffers.size(); ++i) {
        if (!buffers[i]->vazio()) {
            heap.emplace_back(buffers[i]->proximo(), i);
        }
    }
    
    std::make_heap(heap.begin(), heap.end(), comparar);

    while (!heap.empty()) {
        std::pop_heap(heap.begin(), heap.end(), comparar);
        auto menor = heap.back();
        heap.pop_back();

        buffer_saida.inserir(menor.first);

        size_t origem_buffer = menor.second;
        if (!buffers[origem_buffer]->vazio()) {
            heap.emplace_back(buffers[origem_buffer]->proximo(), origem_buffer);
            std::push_heap(heap.begin(), heap.end(), comparar);
        }
    }

    buffer_saida.despejar();
}

void ordenacao_externa(const char* arquivo_entrada, size_t B, size_t S, const char* arquivo_saida) {
    using namespace std::chrono; // Para usar as funções de cronômetro

    size_t tamanho_buffer = B;
    size_t tamanho_subbuffer = S;
    size_t contador_subarquivos = 0;
    
    BufferEntrada buffer_entrada(arquivo_entrada, tamanho_buffer);

    std::vector<std::string> subarquivos;

    // Captura o tempo de início
    auto inicio = high_resolution_clock::now();

    while (!buffer_entrada.vazio()) {
        std::vector<ITEM_VENDA> subbuffer;

        while (!buffer_entrada.vazio() && subbuffer.size() < tamanho_subbuffer) {
            subbuffer.push_back(buffer_entrada.proximo());
        }

        std::sort(subbuffer.begin(), subbuffer.end(), [](const ITEM_VENDA& a, const ITEM_VENDA& b) {
            return a.id < b.id;
        });

        std::string nome_subarquivo = "subarquivo_" + std::to_string(contador_subarquivos++);
        nome_subarquivo += ".bin";
        subarquivos.push_back(nome_subarquivo);

        FILE* f = fopen(nome_subarquivo.c_str(), "wb");
        if (f == nullptr) {
            perror("Erro ao criar subarquivo");
            exit(EXIT_FAILURE);
        }

        fwrite(subbuffer.data(), sizeof(ITEM_VENDA), subbuffer.size(), f);
        fclose(f);
    }

    std::vector<BufferEntrada*> buffers;
    for (const auto& nome_subarquivo : subarquivos) {
        buffers.push_back(new BufferEntrada(nome_subarquivo.c_str(), tamanho_subbuffer));
    }

    BufferSaida buffer_saida(arquivo_saida, tamanho_buffer);

    intercalacao_k_vias(buffers, buffer_saida);

    // Captura o tempo de fim
    auto fim = high_resolution_clock::now();

    // Calcula o tempo decorrido
    auto duracao = duration_cast<milliseconds>(fim - inicio).count();
    std::printf("Tempo de execução: %lld ms\n", static_cast<long long>(duracao));

    for (auto* buffer : buffers) {
        delete buffer;
    }

    for (const auto& nome_subarquivo : subarquivos) {
        remove(nome_subarquivo.c_str());
    }
}
