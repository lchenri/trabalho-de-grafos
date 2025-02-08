#include "../include/aresta_grafo.h"

aresta_grafo::aresta_grafo(int destino, int peso) :
    destino(destino),
    peso(peso),
    proxima(nullptr)
{}

// Destruidor padrão (não é virtual pois não há herança para arestas)
aresta_grafo::~aresta_grafo() = default;