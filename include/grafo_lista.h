#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "no_grafo.h"

class grafo_lista : public grafo {
private:
    no_grafo* primeiro_no;

public:
    grafo_lista();
    ~grafo_lista() override;

    no_grafo* get_no(int id) override;
    aresta_grafo* get_aresta(int origem, int destino) override;
    aresta_grafo* get_vizinhos(int id) override;
    int get_ordem() override;
    bool existe_aresta(int origem, int destino) override;


    void add_no(int id, int peso) override;
    void add_aresta(int origem, int destino, int peso) override;
};

#endif // GRAFO_LISTA_H