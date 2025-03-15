#ifndef NO_GRAFO_H
#define NO_GRAFO_H

#include "aresta_grafo.h"

/**
 * @file no_grafo.h
 * @brief Classe que representa um nó de um grafo.
 * @details Cada nó possui um id, um peso e um ponteiro para a primeira aresta que parte dele.
 */
class no_grafo {
public:
    int id;
    int peso;
    aresta_grafo* primeira_aresta;
    no_grafo* proximo;

    no_grafo(int id, int peso = 0);
    ~no_grafo();
};

#endif // NO_GRAFO_H