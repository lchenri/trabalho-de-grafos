#include "../include/grafo_matriz.h"
#include <iostream>

/**
 * @file grafo_matriz.cpp
 * @brief Implementação da classe grafo_matriz.
 */

/**
 * @brief Construtor da classe grafo_matriz.
 * @details Inicializa a matriz de adjacência como nullptr e a flag de inicialização como false.
 */
grafo_matriz::grafo_matriz() : matriz(nullptr), matriz_inicializada(false) {
    num_nos = 0;
}

/**
 * @brief Destrutor da classe grafo_matriz.
 * @details Deleta a matriz de adjacência e todas as arestas.
 */
grafo_matriz::~grafo_matriz() {
    if (matriz_inicializada) {
        for (int i = 0; i < num_nos; ++i) {
            for (int j = 0; j < num_nos; ++j) {
                delete matriz[i][j];
            }
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz_inicializada = false;
    }
}

/**
 * @brief Retorna um nó do grafo.
 * @param id O id do nó a ser retornado.
 * @return O nó com o id especificado, ou nullptr se ele não existir.
 */
no_grafo* grafo_matriz::get_no(int id) {
    return nullptr;
}

/**
 * @brief Retorna uma aresta do grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @return A aresta que vai do nó de origem para o nó de destino, ou nullptr se ela não existir.
 */
aresta_grafo* grafo_matriz::get_aresta(int origem, int destino) {
    if (origem < 1 || origem > num_nos || destino < 1 || destino > num_nos)
        return nullptr;

    if (!direcionado && origem > destino)
        std::swap(origem, destino);

    return matriz[origem-1][destino-1];
}

/**
 * @brief Retorna as arestas que saem de um nó.
 * @param id O id do nó.
 * @return Um ponteiro para a primeira aresta que sai do nó, ou nullptr se ele não existir.
 */
aresta_grafo* grafo_matriz::get_vizinhos(int id) {
    if (id < 1 || id > num_nos) return nullptr;

    aresta_grafo* cabeca = nullptr;
    aresta_grafo* atual = nullptr;

    for (int j = 0; j < num_nos; ++j) {
        if (matriz[id-1][j] != nullptr) {
            aresta_grafo* nova_aresta = new aresta_grafo(matriz[id-1][j]->destino, matriz[id-1][j]->peso);

            if (!cabeca) {
                cabeca = nova_aresta;
                atual = cabeca;
            } else {
                atual->proxima = nova_aresta;
                atual = atual->proxima;
            }
        }
    }
    return cabeca;
}

/**
 * @brief Retorna a ordem do grafo.
 * @return O número de nós do grafo.
 */
int grafo_matriz::get_ordem() {
    return num_nos;
}

/**
 * @brief Verifica se uma aresta existe no grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @return true se a aresta existe, false caso contrário.
 */
bool grafo_matriz::existe_aresta(int origem, int destino) {
    return get_aresta(origem, destino) != nullptr;
}

/**
 * @brief Adiciona um nó ao grafo.
 * @param id O id do nó a ser adicionado.
 * @param peso O peso do nó a ser adicionado.
 */
void grafo_matriz::add_no(int id, int peso) {
    if (!matriz_inicializada && num_nos > 0) {
        matriz = new aresta_grafo**[num_nos];
        for (int i = 0; i < num_nos; ++i) {
            matriz[i] = new aresta_grafo*[num_nos];
            for (int j = 0; j < num_nos; ++j) {
                matriz[i][j] = nullptr;
            }
        }
        matriz_inicializada = true;
    }
}

/**
 * @brief Adiciona uma aresta ao grafo.
 * @param origem O id do nó de origem da aresta.
 * @param destino O id do nó de destino da aresta.
 * @param peso O peso da aresta.
 */
void grafo_matriz::add_aresta(int origem, int destino, int peso) {
    if (origem == destino) return;

    int i = origem - 1;
    int j = destino - 1;

    if (i >= 0 && i < num_nos && j >= 0 && j < num_nos && !matriz[i][j]) {
        matriz[i][j] = new aresta_grafo(destino, peso);

        if (!direcionado && origem != destino) {
            matriz[j][i] = new aresta_grafo(origem, peso);
        }
    }
}