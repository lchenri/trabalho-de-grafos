#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <functional>

Grafo_Matriz::Grafo_Matriz() : num_vertices(0), num_arestas(0), direcionado(false),

peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),

arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),

componentes_conexas(0) {
}

// Destructor

Grafo_Matriz::~Grafo_Matriz() {}

// Inicializa a matriz de adjac�ncia

void Grafo_Matriz::inicializa_matriz() {
	// Implementar
}

// Adiciona uma aresta � matriz

void Grafo_Matriz::adicionar_aresta(int origem, int destino, int peso) {

	// Implementar

}

// Carrega o grafo a partir de um arquivo

void Grafo_Matriz::carrega_grafo(const std::string& arquivo) {

	// Implementar

}

// Cria um novo grafo a partir de uma descri��o

void Grafo_Matriz::novo_grafo(const std::string& arquivo) {
	// Implementar
}

// Implementa��o das fun��es abstratas

bool Grafo_Matriz::eh_bipartido() {

	// Implementar
	return false;

}

int Grafo_Matriz::n_conexo() {

	// Implementar
	return 0;

}

int Grafo_Matriz::get_grau() {

	// Implementar
	return 0;

}

int Grafo_Matriz::get_ordem() {

	return num_vertices;

}

bool Grafo_Matriz::eh_direcionado() {

	return direcionado;

}

bool Grafo_Matriz::vertice_ponderado() {

	return peso_vertices;

}

bool Grafo_Matriz::aresta_ponderada() {

	return peso_arestas;

}

bool Grafo_Matriz::eh_completo() {

	// Implementar
	return false;

}

bool Grafo_Matriz::eh_arvore() {

	return false;

}

bool Grafo_Matriz::possui_articulacao() {

	// Implementar
	return false;

}

bool Grafo_Matriz::possui_ponte() {

	// Implementar
	return false;

}

void Grafo_Matriz::exibe_descricao() {

	std::cout << "Grau: " << get_grau() << std::endl;

	std::cout << "Ordem: " << get_ordem() << std::endl;

	std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "N�o") << std::endl;

	std::cout << "Componentes conexas: " << n_conexo() << std::endl;

	std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "N�o") << std::endl;

	std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "N�o") << std::endl;

	std::cout << "Completo: " << (eh_completo() ? "Sim" : "N�o") << std::endl;

	std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "N�o") << std::endl;

	std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "N�o") << std::endl;

	std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "N�o") << std::endl;

	std::cout << "Vertice de Articula��o: " << (possui_articulacao() ? "Sim" : "N�o") << std::endl;

}