#include "../include/aresta_grafo.h"

/**
 * @file aresta_grafo.cpp
 * @brief Implementação da classe aresta_grafo.
 */

/**
 * @brief Construtor da classe aresta_grafo.
 * @param destino O vértice de destino da aresta.
 * @param peso O peso da aresta.
 * @details O ponteiro para a próxima aresta é inicializado como nullptr.
 */
aresta_grafo::aresta_grafo(int destino, int peso) :
    destino(destino),
    peso(peso),
    proxima(nullptr)
{}

/**
 * @brief Destrutor da classe aresta_grafo.
 */
aresta_grafo::~aresta_grafo() = default;