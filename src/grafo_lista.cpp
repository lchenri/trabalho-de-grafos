#include "../include/grafo_lista.h"
#include <fstream>

Grafo_Lista::Grafo_Lista() : num_vertices(0), num_arestas(0),
                             direcionado(false),
                             peso_vertices(false), peso_arestas(false), completo(false), bipartido(false),
                             arvore(false), possui_ponte_flag(false), possui_articulacao_flag(false),
                             componentes_conexas(0) {}
// Destructor
Grafo_Lista::~Grafo_Lista() {}
// Adiciona uma aresta à lista
void Grafo_Lista::adicionar_aresta(int origem, int destino, int peso)
{
    //implementar
}
// Carrega o grafo a partir de um arquivo
void Grafo_Lista::carrega_grafo(const std::string &arquivo)
{
    //implementar
}
// Cria um novo grafo a partir de uma descrição
void Grafo_Lista::novo_grafo(const std::string &arquivo)
{
    //implementar
}


// Implementação das funções abstratas
bool Grafo_Lista::eh_bipartido()
{
    //implementar
    return true;
}

int Grafo_Lista::n_conexo()
{
    //implementar
    return 1;
}

int Grafo_Lista::get_grau()
{
    //implementar
    return 1;
}

int Grafo_Lista::get_ordem()
{
    return num_vertices;
}

bool Grafo_Lista::eh_direcionado()
{
    return direcionado;
}

bool Grafo_Lista::vertice_ponderado()
{
    return peso_vertices;
}

bool Grafo_Lista::aresta_ponderada()
{
    return peso_arestas;
}

bool Grafo_Lista::eh_completo()
{
    //implementar
    return true;
}
bool Grafo_Lista::eh_arvore()
{
    //implementar
    return true;
}
bool Grafo_Lista::possui_articulacao()
{
    //implementar
    return false;
}
bool Grafo_Lista::possui_ponte()
{
    //implementar
    return false;
}
void Grafo_Lista::exibe_descricao()
{
    std::cout << "Grau: " << get_grau() << std::endl;
    std::cout << "Ordem: " << get_ordem() << std::endl;
    std::cout << "Direcionado: " << (eh_direcionado() ? "Sim" : "Nao") << std::endl;
    std::cout << "Componentes conexas: " << n_conexo() << std::endl;
    std::cout << "Vertices ponderados: " << (vertice_ponderado() ? "Sim" : "Nao")
              << std::endl;
    std::cout << "Arestas ponderadas: " << (aresta_ponderada() ? "Sim" : "Nao") << std::endl;
    std::cout << "Completo: " << (eh_completo() ? "Sim" : "Nao") << std::endl;
    std::cout << "Bipartido: " << (eh_bipartido() ? "Sim" : "Nao") << std::endl;
    std::cout << "Arvore: " << (eh_arvore() ? "Sim" : "Nao") << std::endl;
    std::cout << "Aresta Ponte: " << (possui_ponte() ? "Sim" : "Nao") << std::endl;
    std::cout << "Vertice de Articulacao: " << (possui_articulacao() ? "Sim" : "Nao") << std::endl;
}

