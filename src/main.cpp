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

bool validar_argumentos(int argc, char *argv[])
{
    if (argc < 4)
    {
        exibir_uso();
        return false;
    }

    std::string modo = argv[1];
    if (modo == "-c" && argc < 5)
    {
        exibir_uso();
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!validar_argumentos(argc, argv))
    {
        return 1;
    }

    std::string modo = argv[1];
    std::string estrutura = argv[2];

    if (modo == "-d")
    {
        std::string arquivo = argv[3];
        // Implementar lógica para modo -d
    }
    else if (modo == "-c")
    {
        std::string descricao = argv[3];
        std::string arquivo = argv[4];
        // Implementar lógica para modo -c
    }

    return 0;
}