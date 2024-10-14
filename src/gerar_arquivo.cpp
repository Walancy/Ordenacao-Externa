#include <cstdio>
#include "../include/big_file.h"

int main(int argc, char** argv) {
    printf("sizeof(ITEM_VENDA) = %ld\n", sizeof(ITEM_VENDA));
    gerar_array_iv("teste_256000.dat", 256000, 42);
    gerar_array_iv("teste_256000.dat", 512000, 42);
    gerar_array_iv("teste_256000.dat", 921600, 42);
    gerar_array_iv("teste_256000.dat", 1572864, 42);
}
