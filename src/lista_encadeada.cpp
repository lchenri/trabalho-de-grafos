#include "../include/lista_encadeada.h"

/**
* @file lista_encadeada.cpp
* @brief Implementação das funções referente à classe ListaVertices e ListaArestas
*/

/**
* @brief Construtor padrão da classe NoVertice
*/
ListaVertices::~ListaVertices() {
    NoVertice *atual = head;
    while (atual) {
        NoVertice *temp = atual;
        atual = atual->prox;

        NoAresta *arestaAtual = temp->arestas;
        while (arestaAtual) {
            NoAresta *tempAresta = arestaAtual;
            arestaAtual = arestaAtual->prox;
            delete tempAresta;
        }

        delete temp;
    }
}

/**
* @brief Adiciona um vértice na lista
* @param id id do vértice
* @param peso peso do vértice
*/
void ListaVertices::adicionar_vertice(int id, int peso) {
    if (buscar_vertice(id)) return;

    NoVertice *novo = new NoVertice(id, peso);
    novo->prox = head;
    head = novo;
}

/**
* @brief Busca um vértice na lista
* @param id id do vértice
* @return ponteiro para o vértice, nullptr se não encontrado
*/
NoVertice *ListaVertices::buscar_vertice(int id) {
    NoVertice *atual = head;
    while (atual) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return nullptr;
}

/**
* @brief Destrutor padrão da classe ListaArestas
*/
ListaArestas::~ListaArestas() {
    NoAresta *atual = head;
    while (atual) {
        NoAresta *temp = atual;
        atual = atual->prox;
        delete temp;
    }
}

/**
 * @brief Adiciona uma aresta na lista
 * @param destino Vértice de destino da aresta
 * @param peso Peso da aresta
 */
void ListaArestas::adicionar_aresta(int destino, int peso) {
    NoAresta* existente = head;
    while (existente) {
        if (existente->destino == destino) return;
        existente = existente->prox;
    }
    NoAresta* novo = new NoAresta(destino, peso);
    novo->prox = head;
    head = novo;
}
