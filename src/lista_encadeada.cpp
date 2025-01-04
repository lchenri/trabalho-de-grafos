#include "../include/lista_encadeada.h"

// Implementação do destrutor da ListaVertices
ListaVertices::~ListaVertices()
{
    NoVertice *atual = head;
    while (atual)
    {
        NoVertice *temp = atual;
        atual = atual->prox;

        // Libera a lista de arestas do vértice
        NoAresta *arestaAtual = temp->arestas;
        while (arestaAtual)
        {
            NoAresta *tempAresta = arestaAtual;
            arestaAtual = arestaAtual->prox;
            delete tempAresta;
        }

        delete temp;
    }
}

// Adicionar um vértice na lista
void ListaVertices::adicionar_vertice(int id, int peso)
{
    if (buscar_vertice(id)) return;

    NoVertice *novo = new NoVertice(id, peso);
    novo->prox = head;
    head = novo;
}

// Buscar um vértice pelo id
NoVertice *ListaVertices::buscar_vertice(int id)
{
    NoVertice *atual = head;
    while (atual)
    {
        if (atual->id == id)
        {
            return atual;
        }
        atual = atual->prox;
    }
    return nullptr; // Vértice não encontrado
}

// Implementação do destrutor da ListaArestas
ListaArestas::~ListaArestas()
{
    NoAresta *atual = head;
    while (atual)
    {
        NoAresta *temp = atual;
        atual = atual->prox;
        delete temp;
    }
}

// Adicionar uma aresta na lista
void ListaArestas::adicionar_aresta(int destino, int peso)
{
    NoAresta* existente = head;
    while (existente) {
        if (existente->destino == destino) return; // Evita múltiplas arestas
        existente = existente->prox;
    }
    NoAresta* novo = new NoAresta(destino, peso);
    novo->prox = head;
    head = novo;
}
