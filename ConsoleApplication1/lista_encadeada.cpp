#include "lista_encadeada.h"

// Destructor para ListaVertices

ListaVertices::~ListaVertices() {

	//implementar

}

// Adiciona um v�rtice � lista

void ListaVertices::adicionar_vertice(int id, int peso) {

	//implementar

}

// Busca um v�rtice pelo ID

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

// Adiciona uma aresta � lista

void ListaArestas::adicionar_aresta(int destino, int peso) {

	//implementar

}