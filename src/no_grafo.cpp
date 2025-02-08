#include "../include/no_grafo.h"
#include "../include/aresta_grafo.h"

no_grafo::no_grafo(int id, int peso) :
    id(id),
    peso(peso),
    primeira_aresta(nullptr),
    proximo(nullptr)
{}

no_grafo::~no_grafo() {
    aresta_grafo* atual = primeira_aresta;
    while (atual) {
        aresta_grafo* proxima = atual->proxima;
        delete atual;
        atual = proxima;
    }
}