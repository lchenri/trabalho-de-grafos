#include <iostream>
#include <cstring>

#include "../include/grafo_lista.h"
#include "../include/grafo_matriz.h"

void exibir_uso()
{
    std::cout << "Uso:\n";
    std::cout << "Caso 1: main.out -d -m grafo.txt\n";
    std::cout << "Caso 2: main.out -d -l grafo.txt\n";
    std::cout << "Caso 3: main.out -c -m descricao.txt grafo.txt\n";
    std::cout << "Caso 4: main.out -c -l descricao.txt grafo.txt\n";
}
int main(int argc, char *argv[])
{
    exibir_uso();
    return 0;
}