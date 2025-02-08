#include "../include/grafo.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

/**
 * @file grafo.cpp
 * @brief Implementação da classe grafo.
 */

grafo::grafo() {}

/**
 * @brief Constroi o grafo a partir de um arquivo.
 * @param arquivo O caminho para o arquivo contendo a descrição do grafo.
 */
void grafo::carrega_grafo(const std::string& arquivo) {

    std::ifstream file(arquivo);
    if (!file.is_open()) throw std::runtime_error("Arquivo não encontrado");

    int num_nos, dir, pond_vertices, pond_arestas;
    file >> num_nos >> dir >> pond_vertices >> pond_arestas;

    this->direcionado = dir;
    this->ponderado_vertices = pond_vertices;
    this->ponderado_arestas = pond_arestas;
    this->num_nos = num_nos;

    if (ponderado_vertices) {
        for (int i = 1; i <= num_nos; ++i) {
            int peso;
            file >> peso;
            add_no(i, peso);
        }
    } else {
        for (int i = 1; i <= num_nos; ++i) {
            add_no(i, 0);
        }
    }

    int origem, destino, peso = 0;
    while (file >> origem >> destino) {
        if (ponderado_arestas) file >> peso;
        add_aresta(origem, destino, peso);
    }
}

/**
 * @brief Verifica se o grafo é completo.
 * @return true se o grafo é completo, false caso contrário.
 */
bool grafo::eh_completo() {
    int n = get_ordem();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != j && !existe_aresta(i, j)) {
                if (direcionado) return false;
                if (!existe_aresta(j, i)) return false;
            }
        }
    }
    return true;
}

/**
 * @brief Libera a memória alocada para as arestas temporárias.
 * @param cabeca O ponteiro para a primeira aresta.
 */
void liberar_arestas_temp(aresta_grafo* cabeca) {
    while (cabeca) {
        aresta_grafo* temp = cabeca;
        cabeca = cabeca->proxima;
        delete temp; // Libera apenas a cópia
    }
}

/**
 * @brief Retorna o grau do grafo.
 * @return O grau do grafo.
 */
int grafo::get_grau() {
    int grau_maximo = 0;
    for (int i = 1; i <= get_ordem(); ++i) {
        int grau_atual = 0;

        aresta_grafo* vizinhos = get_vizinhos(i);
        aresta_grafo* atual = vizinhos;
        while (atual) {
            grau_atual++;
            atual = atual->proxima;
        }

        liberar_arestas_temp(vizinhos);

        if (direcionado) {
            for (int j = 1; j <= get_ordem(); ++j) {
                if (existe_aresta(j, i)) grau_atual++;
            }
        }

        if (grau_atual > grau_maximo) grau_maximo = grau_atual;
    }
    return grau_maximo;
}

/**
 * @brief Exibe a descrição do grafo.
 */
void grafo::exibe_descricao() {
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
}

/**
 * @brief Funções que retornam as flags: direcionado, ponderado_vertices e ponderado_arestas.
 */
bool grafo::eh_direcionado() const { return direcionado; }
bool grafo::vertice_ponderado() const { return ponderado_vertices; }
bool grafo::aresta_ponderada() const { return ponderado_arestas; }

