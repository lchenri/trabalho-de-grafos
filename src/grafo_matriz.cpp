#include "../include/grafo_matriz.h"

#include <iostream>
#include <ostream>
#include <vector>
#include <stdexcept>

grafo_matriz::grafo_matriz() {
	num_nos = 0;
}

grafo_matriz::~grafo_matriz() {
	for (auto& linha : matriz) {
		for (auto aresta : linha) {
			delete aresta; // Libera cada aresta da matriz
		}
	}
}

no_grafo* grafo_matriz::get_no(int id) {
	// Não aplicável para matriz, pois vértices são estáticos
	return nullptr;
}

aresta_grafo* grafo_matriz::get_aresta(int origem, int destino) {
	if (origem < 1 || origem > num_nos || destino < 1 || destino > num_nos)
		return nullptr;

	if (!direcionado && origem > destino)
		std::swap(origem, destino);

	return matriz[origem-1][destino-1];
}

aresta_grafo* grafo_matriz::get_vizinhos(int id) {
	if (id < 1 || id > num_nos) return nullptr;

	aresta_grafo* cabeca = nullptr;
	aresta_grafo* atual = nullptr;

	// Percorre toda a linha da matriz
	for (int j = 0; j < num_nos; ++j) {
		if (matriz[id-1][j] != nullptr) {
			// Cria uma cópia da aresta para a lista de vizinhos
			aresta_grafo* nova_aresta = new aresta_grafo(matriz[id-1][j]->destino, matriz[id-1][j]->peso);

			if (!cabeca) {
				cabeca = nova_aresta;
				atual = cabeca;
			} else {
				atual->proxima = nova_aresta;
				atual = atual->proxima;
			}
		}
	}
	return cabeca;
}

int grafo_matriz::get_ordem() {
	return num_nos;
}

bool grafo_matriz::existe_aresta(int origem, int destino) {
	return get_aresta(origem, destino) != nullptr;
}

void grafo_matriz::add_no(int id, int peso) {
	// Inicializa a matriz apenas uma vez
	if (matriz.empty() && num_nos > 0) {
		matriz.resize(num_nos, std::vector<aresta_grafo*>(num_nos, nullptr));
	}
}

void grafo_matriz::add_aresta(int origem, int destino, int peso) {
	if (origem == destino) return; // Ignora laços

	int i = origem - 1;
	int j = destino - 1;

	// Garante índices válidos
	if (i >= 0 && i < num_nos && j >= 0 && j < num_nos && !matriz[i][j]) {
		matriz[i][j] = new aresta_grafo(destino, peso);

		// Grafos não direcionados: adiciona na posição inversa
		if (!direcionado && origem != destino) {
			matriz[j][i] = new aresta_grafo(origem, peso);
		}
	}
}
