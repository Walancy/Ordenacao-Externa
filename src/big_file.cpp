#include "../include/big_file.h"
#include "../include/prandom.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

static inline void trocar(ITEM_VENDA& x, ITEM_VENDA& y){
    ITEM_VENDA aux;
    aux = x;
    x = y;
    y = aux;
}

static void embaralhar(ITEM_VENDA* v, int ini, int fim){
    int i, j;

    for(i = fim-1; i > ini; i--){
        j = (rand_() % (i + 1));
        j = j <= ini ? ini+1 : j;
        trocar(v[i], v[j]);
    }
}

void gerar_array_iv(const char* arquivo_saida, unsigned int n_registros, int seed){
    ITEM_VENDA* iv;
    FILE* saida;
    uint32_t i;
    time_t t = time(NULL);
    
    srand(seed);  // Inicializa o gerador de números aleatórios com o seed fornecido

    // Alocação de memória para o array de registros ITEM_VENDA
    iv = (ITEM_VENDA*) malloc(sizeof(ITEM_VENDA) * n_registros);
    if (iv == NULL) {
        fprintf(stderr, "Erro ao alocar memória para ITEM_VENDA.\n");
        exit(1);
    }

    // Preenchimento do array com dados
    for(i = 0; i < n_registros; i++){
        iv[i].id = i;
        iv[i].id_venda = i + (rand() % 2);
        iv[i].desconto = (rand() % 10) / (float)100;
        iv[i].data = t + ((-1 * (rand() % 30)) * 86400);
        iv[i].desc[0] = '\0';
    }

    // Embaralhamento dos registros
    embaralhar(iv, 0, n_registros);

    // Abertura do arquivo binário para escrita
    saida = fopen(arquivo_saida, "wb");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        free(iv);  // Libera a memória antes de sair
        exit(1);
    }

    // Escrita dos registros no arquivo
    size_t written = fwrite(iv, sizeof(ITEM_VENDA), n_registros, saida);
    if (written != n_registros) {
        fprintf(stderr, "Erro ao escrever os registros no arquivo. Registros escritos: %zu\n", written);
    }

    // Fechamento do arquivo e liberação de memória
    fclose(saida);
    free(iv);

    printf("Arquivo '%s' gerado com sucesso. Total de registros: %u\n", arquivo_saida, n_registros);
}
