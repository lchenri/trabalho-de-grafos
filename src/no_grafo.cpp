#include "../include/no_grafo.h"
#include "../include/aresta_grafo.h"

/**
 * @file no_grafo.cpp
 * @brief Implementação da classe no_grafo.
 */

/**
 * @brief Construtor da classe no_grafo.
 * @param id O id do nó.
 * @param peso O peso do nó.
 * @details O ponteiro para a primeira aresta é inicializado como nullptr.
 */
no_grafo::no_grafo(int id, int peso) :
    id(id),
    peso(peso),
    primeira_aresta(nullptr),
    proximo(nullptr)
{}

/**
 * @brief Destrutor da classe no_grafo.
 * @details Deleta todas as arestas do nó.
 */
no_grafo::~no_grafo() {
    aresta_grafo* atual = primeira_aresta;
    while (atual) {
        aresta_grafo* temp = atual;
        atual = atual->proxima;
        delete temp;
    }
}