#ifndef ARESTA_GRAFO_H
#define ARESTA_GRAFO_H

/**
 * @file aresta_grafo.h
 * @brief Classe que representa uma aresta de um grafo.
 * @details Cada aresta possui um destino, que é o vértice para o qual ela aponta, um peso, que é o custo para se chegar ao vértice de destino, e um ponteiro para a próxima aresta.
 */
class aresta_grafo {
public:
    int destino;
    int peso;
    aresta_grafo* proxima;

    aresta_grafo(int destino, int peso = 0);

    ~aresta_grafo();
};

#endif // ARESTA_GRAFO_H