#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

/**
 * @file grafo_matriz.h
 * @brief Classe que representa um grafo implementado com matriz de adjacência.
 * @details Cada nó do grafo possui um id e um peso, e cada aresta possui um destino, um peso e um ponteiro para a próxima aresta.
 */
class grafo_matriz : public grafo {
private:
    aresta_grafo*** matriz;
    bool matriz_inicializada;

public:
    grafo_matriz();
    ~grafo_matriz() override;

    no_grafo* get_no(int id) override;
    aresta_grafo* get_aresta(int origem, int destino) override;
    aresta_grafo* get_vizinhos(int id) override;
    int get_ordem() override;
    bool existe_aresta(int origem, int destino) override;

    void add_no(int id, int peso) override;
    void add_aresta(int origem, int destino, int peso) override;
};

#endif // GRAFO_MATRIZ_H