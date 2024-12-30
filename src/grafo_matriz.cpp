#include "../include/grafo_matriz.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>

Grafo_Matriz::Grafo_Matriz() : num_vertices(0), num_arestas(0), direcionado(false),

                               peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),

                               arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),

                               componentes_conexas(0) {
}

// Destructor

Grafo_Matriz::~Grafo_Matriz() {}

// Inicializa a matriz de adjac�ncia

void Grafo_Matriz::inicializa_matriz() {
	// Inicializa a matriz quadrada de tamanho num_vertices e atribui 0 para cada posição.
	matriz_adjacencia.resize(num_vertices, std::vector<int>(num_vertices, 0));
}

// Adiciona uma aresta � matriz

void Grafo_Matriz::adicionar_aresta(int origem, int destino, int peso) {
	matriz_adjacencia[origem][destino] = peso;
	num_arestas++;
}

// Carrega o grafo a partir de um arquivo

void Grafo_Matriz::carrega_grafo(const std::string& arquivo) {
	std::ifstream arquivo_entrada(arquivo);

	if (!arquivo_entrada.is_open()) {
		std::cerr << "Não foi possível abrir o arquivo." << std::endl;
	}

	arquivo_entrada >> num_vertices >> direcionado >> peso_vertices >> peso_arestas;
	inicializa_matriz();

	if (peso_vertices) {
		std::string linha;
		std::getline(arquivo_entrada, linha); // lê até o final da linha
		std::getline(arquivo_entrada, linha); // lê a linha com os pesos dos vértices
		std::istringstream iss(linha);
		int peso;
		while (iss >> peso) {
			this->pesos_vertices.push_back(peso);
		}
	}

	int origem, destino, peso;
	while (arquivo_entrada >> origem >> destino >> peso) {
		adicionar_aresta(origem, destino, peso);
	}
}

// Cria um novo grafo a partir de uma descri��o
void Grafo_Matriz::novo_grafo(const std::string& descricao, std::string& arquivo) {
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