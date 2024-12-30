#ifndef GRAFO_H
#define GRAFO_H
#include <string>

class Grafo{
public:
    virtual ~Grafo() {}
    // Verifica se o grafo é bipartido
    virtual bool eh_bipartido() = 0;
    // Retorna o número de componentes conexas
    virtual int n_conexo() = 0;
    // Retorna o grau do grafo
    virtual int get_grau() = 0;
    // Retorna a ordem do grafo
    virtual int get_ordem() = 0;
    // Verifica se o grafo é direcionado
    virtual bool eh_direcionado() = 0;
    // Verifica se os vértices possuem peso
    virtual bool vertice_ponderado() = 0;
    // Verifica se as arestas possuem peso
    virtual bool aresta_ponderada() = 0;
    // Verifica se o grafo é completo
    virtual bool eh_completo() = 0;
    // Verifica se o grafo é uma árvore
    virtual bool eh_arvore() = 0;
    // Verifica se existe vértice de articulação
    virtual bool possui_articulacao() = 0;
    // Verifica se existe aresta ponte
    virtual bool possui_ponte() = 0;
    // Carrega o grafo a partir de um arquivo
    virtual void carrega_grafo(const std::string &arquivo) = 0;
    // Cria um novo grafo a partir de uma descrição
    virtual void novo_grafo(const std::string &arquivo) = 0;
    // Exibe a descrição do grafo
    virtual void exibe_descricao() = 0;
};

#endif //GRAFO_H
