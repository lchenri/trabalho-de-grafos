#include "grafo_lista.h"

#include <fstream>

#include <sstream>

#include <queue>

Grafo_Lista::Grafo_Lista() : num_vertices(0), num_arestas(0), direcionado(false),

peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),

arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),

componentes_conexas(0) {
}

// Destructor

Grafo_Lista::~Grafo_Lista() {}

// Adiciona uma aresta à lista

void Grafo_Lista::adicionar_aresta(int origem, int destino, int peso) {

	//implementar

}

// Carrega o grafo a partir de um arquivo

void Grafo_Lista::carrega_grafo(const std::string& arquivo) {

	// implementar

}

// Cria um novo grafo a partir de uma descrição

void Grafo_Lista::novo_grafo(const std::string& arquivo) {

	// implementar
}

// Implementação das funções abstratas

bool Grafo_Lista::eh_bipartido() {

	// implementar

	return true; 

}

int Grafo_Lista::n_conexo() {

	// implementar

	return 1;

}

int Grafo_Lista::get_grau() {

	// implementar

}

int Grafo_Lista::get_ordem() {

	return num_vertices;

}

bool Grafo_Lista::eh_direcionado() {

	return direcionado;

}

bool Grafo_Lista::vertice_ponderado() {

	return peso_vertices;

}

bool Grafo_Lista::aresta_ponderada() {

	return peso_arestas;

}

bool Grafo_Lista::eh_completo() {

	// implementar
	return false;

}

bool Grafo_Lista::eh_arvore() {

	// implementar

}

bool Grafo_Lista::possui_articulacao() {

	// Implementar

	return false;

}

bool Grafo_Lista::possui_ponte() {

	// implementar

	return false; 

}

void Grafo_Lista::exibe_descricao() {

	std::cout << "Grau: " << get_grau() << std::endl;

	std::cout << "Ordem: " << get_ordem() << std::endl;

	std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Não") << std::endl;

	std::cout << "Componentes conexas: " << n_conexo() << std::endl;

	std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Não") << std::endl;

	std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Não") << std::endl;

	std::cout << "Completo: " << (eh_completo() ? "Sim" : "Não") << std::endl;

	std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Não") << std::endl;

	std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "Não") << std::endl;

	std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Não") << std::endl;

	std::cout << "Vertice de Articulação: " << (possui_articulacao() ? "Sim" : "Não") << std::endl;

}