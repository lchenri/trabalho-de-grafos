#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

std::string debug_matriz_adjacencia(const std::vector<std::vector<int>>& matriz) {
    std::string result;
    for (size_t i = 1; i < matriz.size(); ++i) {
        const auto& linha = matriz[i];
        for (size_t j = 1; j < linha.size(); j++) {
            result += std::to_string(linha[j]) + " ";
        }
        result += "\n";
    }
    return result;
}

std::string debug_matriz_ligacoes(int matriz[MAX_VERTICES][MAX_VERTICES], int num_arestas) {
    std::string result;
    for (int i = 1; i < MAX_VERTICES; ++i) {
        for (int j = 1; j < MAX_VERTICES; ++j) {
            result += std::to_string(matriz[i][j]) + " ";
        }
        result += "\n";
    }
    result += "Número de arestas: " + std::to_string(num_arestas) + "\n";
    return result;
}

std::string debug_lista_adjacencia(const ListaVertices& vertices, int num_arestas) {
    std::string result;
    NoVertice* atual = vertices.head;
    while (atual) {
        result += std::to_string(atual->id) + " -> ";
        NoAresta* arestaAtual = atual->arestas;
        while (arestaAtual)
        {
            result += std::to_string(arestaAtual->destino);
            arestaAtual = arestaAtual->prox;
            if (arestaAtual) {
                result += " -> ";
            }
        }
        result += "\n";
        atual = atual->prox;
    }
    result += "Número de arestas: " + std::to_string(num_arestas) + "\n";
    return result;
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
            std::string foo = "foo";
        }else if (estrutura == "-l") {
            Grafo_Lista grafo;
            grafo.carrega_grafo(arquivo);
            grafo.exibe_descricao();
            std::string foo = "foo";
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