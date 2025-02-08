#ifndef NO_GRAFO_H
#define NO_GRAFO_H

#include "aresta_grafo.h"

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