#pragma once
#pragma once

#ifndef LISTA_ENCADEADA_H

#define LISTA_ENCADEADA_H

#include <iostream>

// Estrutura para um n� de aresta

struct NoAresta {

	int destino;

	int peso;

	NoAresta* prox;

	NoAresta(int dest, int p = 0) : destino(dest), peso(p), prox(nullptr) {}

};

// Estrutura para um n� de v�rtice

struct NoVertice {

	int id;

	int peso;

	NoVertice* prox;

	NoAresta* arestas;

	NoVertice(int identificacao, int p = 0) : id(identificacao), peso(p), prox(nullptr), arestas(nullptr) {}

};

// Classe para lista de v�rtices

class ListaVertices {

public:

	NoVertice* head;

	ListaVertices() : head(nullptr) {}

	~ListaVertices();

	void adicionar_vertice(int id, int peso = 0);

	NoVertice* buscar_vertice(int id);

};

// Classe para lista de arestas (por v�rtice)

class ListaArestas {

public:

	NoAresta* head;

	ListaArestas() : head(nullptr) {}

	~ListaArestas();

	void adicionar_aresta(int destino, int peso = 0);

};

#endif // LISTA_ENCADEADA_H
