#include "../include/grafo_matriz.h"
#include <iostream>

grafo_matriz::grafo_matriz() : matriz(nullptr), matriz_inicializada(false) {
    num_nos = 0;
}

grafo_matriz::~grafo_matriz() {
    if (matriz_inicializada) {
        for (int i = 0; i < num_nos; ++i) {
            for (int j = 0; j < num_nos; ++j) {
                delete matriz[i][j];
            }
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz_inicializada = false;
    }
}

no_grafo* grafo_matriz::get_no(int id) {
    return nullptr;
}

aresta_grafo* grafo_matriz::get_aresta(int origem, int destino) {
    if (origem < 1 || origem > num_nos || destino < 1 || destino > num_nos)
        return nullptr;

    if (!direcionado && origem > destino)
        std::swap(origem, destino);

    return matriz[origem-1][destino-1];
}

aresta_grafo* grafo_matriz::get_vizinhos(int id) {
    if (id < 1 || id > num_nos) return nullptr;

    aresta_grafo* cabeca = nullptr;
    aresta_grafo* atual = nullptr;

    for (int j = 0; j < num_nos; ++j) {
        if (matriz[id-1][j] != nullptr) {
            aresta_grafo* nova_aresta = new aresta_grafo(matriz[id-1][j]->destino, matriz[id-1][j]->peso);

            if (!cabeca) {
                cabeca = nova_aresta;
                atual = cabeca;
            } else {
                atual->proxima = nova_aresta;
                atual = atual->proxima;
            }
        }
    }
    return cabeca;
}

int grafo_matriz::get_ordem() {
    return num_nos;
}

bool grafo_matriz::existe_aresta(int origem, int destino) {
    return get_aresta(origem, destino) != nullptr;
}

void grafo_matriz::add_no(int id, int peso) {
    if (!matriz_inicializada && num_nos > 0) {
        matriz = new aresta_grafo**[num_nos];
        for (int i = 0; i < num_nos; ++i) {
            matriz[i] = new aresta_grafo*[num_nos];
            for (int j = 0; j < num_nos; ++j) {
                matriz[i][j] = nullptr;
            }
        }
        matriz_inicializada = true;
    }
}

void grafo_matriz::add_aresta(int origem, int destino, int peso) {
    if (origem == destino) return;

    int i = origem - 1;
    int j = destino - 1;

    if (i >= 0 && i < num_nos && j >= 0 && j < num_nos && !matriz[i][j]) {
        matriz[i][j] = new aresta_grafo(destino, peso);

        if (!direcionado && origem != destino) {
            matriz[j][i] = new aresta_grafo(origem, peso);
        }
    }
}