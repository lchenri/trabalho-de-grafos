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

    if ( const std::string modo = argv[1];modo == "-c" && argc < 5)
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

    const std::string modo = argv[1];
    const std::string estrutura = argv[2];

    if (modo == "-d")
    {
        const std::string arquivo = argv[3];
        if (estrutura == "-m") {
            Grafo_Matriz grafo;
            grafo.carrega_grafo(arquivo);
            grafo.exibe_descricao();
        }else if (estrutura == "-l") {
            Grafo_Lista grafo;
            grafo.carrega_grafo(arquivo);
            grafo.exibe_descricao();
        }else {
            exibir_uso();
            return 1;
        }
    }
    else if (modo == "-c")
    {
        std::string descricao = argv[3];
        std::string arquivo = argv[4];
        if (estrutura == "-m") {
            Grafo_Matriz grafo;
            grafo.novo_grafo(descricao, arquivo);
            std::cout << "Novo grafo criado e salvo em " << arquivo << " usando matriz de adjacência" << std::endl;
        }else if (estrutura == "-l") {
            Grafo_Lista grafo;
            grafo.novo_grafo(descricao, arquivo);
            std::cout << "Novo grafo criado e salvo em " << arquivo << " usando lista encadeada" << std::endl;
        } else {
            exibir_uso();
            return 1;
        }
    }
    else
    {
        exibir_uso();
        return 1;
    }
    return 0;
}