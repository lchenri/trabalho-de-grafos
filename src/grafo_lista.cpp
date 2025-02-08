#include "../include/grafo_lista.h"

grafo_lista::grafo_lista() : primeiro_no(nullptr) {}

grafo_lista::~grafo_lista() {
    no_grafo* atual = primeiro_no;
    while (atual) {
        no_grafo* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

no_grafo* grafo_lista::get_no(int id) {
    no_grafo* atual = primeiro_no;
    while (atual) {
        if (atual->id == id) return atual;
        atual = atual->proximo;
    }
    return nullptr;
}

aresta_grafo* grafo_lista::get_aresta(int origem, int destino) {
    no_grafo* no_origem = get_no(origem);
    if (!no_origem) return nullptr;

    aresta_grafo* atual = no_origem->primeira_aresta;
    while (atual) {
        if (atual->destino == destino) return atual;
        atual = atual->proxima;
    }
    return nullptr;
}

aresta_grafo* grafo_lista::get_vizinhos(int id) {
    no_grafo* no = get_no(id);
    return no ? no->primeira_aresta : nullptr;
}

int grafo_lista::get_ordem() {
    int count = 0;
    no_grafo* atual = primeiro_no;
    while (atual) {
        count++;
        atual = atual->proximo;
    }
    return count;
}

bool grafo_lista::existe_aresta(int origem, int destino) {
    return get_aresta(origem, destino) != nullptr;
}

void grafo_lista::add_no(int id, int peso) {
    if (get_no(id)) return;

    no_grafo* novo_no = new no_grafo(id, peso);
    novo_no->proximo = primeiro_no;
    primeiro_no = novo_no;
}

void grafo_lista::add_aresta(int origem, int destino, int peso) {
    if (origem == destino) return;

    no_grafo* no_origem = get_no(origem);
    no_grafo* no_destino = get_no(destino);

    if (!no_origem || !no_destino) return;

    if (existe_aresta(origem, destino)) return;

    aresta_grafo* nova_aresta = new aresta_grafo(destino, peso);
    nova_aresta->proxima = no_origem->primeira_aresta;
    no_origem->primeira_aresta = nova_aresta;

    if (!direcionado) {
        aresta_grafo* aresta_inversa = new aresta_grafo(origem, peso);
        aresta_inversa->proxima = no_destino->primeira_aresta;
        no_destino->primeira_aresta = aresta_inversa;
    }
}

