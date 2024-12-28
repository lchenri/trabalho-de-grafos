#include "lista_encadeada.h"

// Destructor para ListaVertices

ListaVertices::~ListaVertices() {

	//implementar

}

// Adiciona um vértice à lista

void ListaVertices::adicionar_vertice(int id, int peso) {

	//implementar

}

// Busca um vértice pelo ID

NoVertice* ListaVertices::buscar_vertice(int id) {

	//implementar

	return NULL;

}

// Destructor para ListaArestas

ListaArestas::~ListaArestas() {

	NoAresta* atual = head;

	while (atual) {

		NoAresta* temp = atual;

		atual = atual->prox;

		delete temp;

	}

}

// Adiciona uma aresta à lista

void ListaArestas::adicionar_aresta(int destino, int peso) {

	//implementar

}