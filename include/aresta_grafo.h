//
// Created by lucas on 08/02/2025.
//

#ifndef ARESTA_GRAFO_HPP
#define ARESTA_GRAFO_HPP

class aresta_grafo {
public:
    int destino;
    int peso;
    aresta_grafo* proxima;

    aresta_grafo(int destino, int peso = 0);

    ~aresta_grafo();
};

#endif // ARESTA_GRAFO_HPP