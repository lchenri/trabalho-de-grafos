#ifndef GRAFO_H
#define GRAFO_H
#include <string>
#include "no_grafo.h"
#include "aresta_grafo.h"

/**
* @file grafo.h
* @brief Classe abstrata que define as operações que podem ser realizadas em um grafo.
* @details Essa classe possui duas filhas: grafo_matriz e grafos_lista, que implementam as operações definidas aqui.
*/


class grafo {
protected:
    bool direcionado;
    bool ponderado_vertices;
    bool ponderado_arestas;
    int num_nos;

public:
    grafo();
    virtual ~grafo() = default;

    virtual no_grafo* get_no(int id) = 0;
    virtual aresta_grafo* get_aresta(int origem, int destino) = 0;
    virtual aresta_grafo* get_vizinhos(int id) = 0;
    virtual int get_ordem() = 0;
    virtual bool existe_aresta(int origem, int destino) = 0;

    int get_grau();
    bool eh_completo();
    bool eh_direcionado() const;
    bool vertice_ponderado() const;
    bool aresta_ponderada() const;
    void carrega_grafo(const std::string& arquivo);

    void exibe_descricao();

    virtual void add_no(int id, int peso) = 0;
    virtual void add_aresta(int origem, int destino, int peso) = 0;
};

#endif //GRAFO_H
