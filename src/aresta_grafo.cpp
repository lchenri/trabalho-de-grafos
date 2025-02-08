#include "../include/aresta_grafo.h"

aresta_grafo::aresta_grafo(int destino, int peso) :
    destino(destino),
    peso(peso),
    proxima(nullptr)
{}

aresta_grafo::~aresta_grafo() = default;