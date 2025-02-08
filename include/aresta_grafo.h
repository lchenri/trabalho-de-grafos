#ifndef ARESTA_GRAFO_H
#define ARESTA_GRAFO_H

class aresta_grafo {
public:
    int destino;
    int peso;
    aresta_grafo* proxima;

    aresta_grafo(int destino, int peso = 0);

    ~aresta_grafo();
};

#endif // ARESTA_GRAFO_H