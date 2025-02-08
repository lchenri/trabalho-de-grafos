#include "../include/grafo.h"

#include <fstream>
#include <iostream>
#include <stdexcept>


grafo::grafo() {}

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

int grafo::get_grau() {
    int grau_maximo = 0;
    for(int i = 1; i <= get_ordem(); ++i){
        int grau_atual = 0;
        
        aresta_grafo* aresta = get_vizinhos(i);
        aresta_grafo* current = aresta;
        while(current){
            grau_atual++;
            current = current->proxima;
        }
        
        while(aresta) {
            aresta_grafo* temp = aresta;
            aresta = aresta->proxima;
            delete temp;
        }
        
        if(direcionado){
            for(int j = 1; j <= get_ordem(); ++j){
                if(existe_aresta(j,i)) grau_atual++;
            }
        }
        
        if(grau_atual > grau_maximo) grau_maximo = grau_atual;
    }
    return grau_maximo;
}


void grafo::exibe_descricao() {
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
}


bool grafo::eh_direcionado() const { return direcionado; }
bool grafo::vertice_ponderado() const { return ponderado_vertices; }
bool grafo::aresta_ponderada() const { return ponderado_arestas; }

